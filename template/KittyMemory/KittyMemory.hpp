#pragma once
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <vector>
#ifdef __APPLE__
#include <mach/mach.h>
#include <mach-o/dyld.h>
#include <mach-o/getsect.h>
#include <libkern/OSCacheControl.h>
#endif
#include "KittyUtils.hpp"
#define KT_PAGE_SIZE (sysconf(_SC_PAGE_SIZE))
#define KT_PAGE_START(x) (uintptr_t(x) & ~(KT_PAGE_SIZE - 1))
#define KT_PAGE_END(x) (KT_PAGE_START(uintptr_t(x) + KT_PAGE_SIZE - 1))
#define KT_PAGE_OFFSET(x) (uintptr_t(x) - KT_PAGE_START(x))
#define KT_PAGE_LEN(x) (size_t(KT_PAGE_SIZE - KT_PAGE_OFFSET(x)))
#define KT_PAGE_END2(x, len) (KT_PAGE_START(uintptr_t(x) + len - 1))
#define KT_PAGE_LEN2(x, len) (KT_PAGE_END2(x, len) - KT_PAGE_START(x) + KT_PAGE_SIZE)
#define _PROT_RWX_ (PROT_READ | PROT_WRITE | PROT_EXEC)
#define _PROT_RX_ (PROT_READ | PROT_EXEC)
#define _PROT_RW_ (PROT_READ | PROT_WRITE)
#define KITTY_LOG_TAG "KittyMemory"
#ifdef __ANDROID__
#include <android/log.h>
#ifdef kITTYMEMORY_DEBUG
#define KITTY_LOGD(fmt, ...) ((void)__android_log_print(ANDROID_LOG_DEBUG, KITTY_LOG_TAG, fmt, ##__VA_ARGS__))
#else
#define KITTY_LOGD(fmt, ...) do {} while(0)
#endif
#define KITTY_LOGI(fmt, ...) ((void)__android_log_print(ANDROID_LOG_INFO, KITTY_LOG_TAG, fmt,  ##__VA_ARGS__))
#define KITTY_LOGE(fmt, ...) ((void)__android_log_print(ANDROID_LOG_ERROR, KITTY_LOG_TAG, fmt, ##__VA_ARGS__))
#elif __APPLE__
#include <os/log.h>
#ifdef kITTYMEMORY_DEBUG
#define KITTY_LOGD(fmt, ...) os_log(OS_LOG_DEFAULT, "D " KITTY_LOG_TAG ": " fmt, ##__VA_ARGS__)
#else
#define KITTY_LOGD(fmt, ...) do {} while(0)
#endif
#define KITTY_LOGI(fmt, ...) os_log(OS_LOG_DEFAULT, "I " KITTY_LOG_TAG ": " fmt, ##__VA_ARGS__)
#define KITTY_LOGE(fmt, ...) os_log_error(OS_LOG_DEFAULT, "E " KITTY_LOG_TAG ": " fmt, ##__VA_ARGS__)
#endif
namespace KittyMemory
{
    int setAddressProtection(const void *address, size_t length, int protection);
    bool memRead(const void *address, void *buffer, size_t len);
#ifdef __ANDROID__

    class ProcMap {
    public:
        unsigned long long startAddress;
        unsigned long long endAddress;
        size_t length;
        int protection;
        bool readable, writeable, executable, is_private, is_shared, is_ro, is_rw, is_rx;
        unsigned long long offset;
        std::string dev;
        unsigned long inode;
        std::string pathname;
        ProcMap() : startAddress(0), endAddress(0), length(0), protection(0),
		            readable(false), writeable(false), executable(false),
                    is_private(false), is_shared(false),
                    is_ro(false), is_rw(false), is_rx(false),
                    offset(0), inode(0) {}
        inline bool isValid() const { return (startAddress && endAddress && length); }
        inline bool isUnknown() const { return pathname.empty(); }
        inline bool isValidELF() const { return isValid() && length > 4 && readable && memcmp((const void *) startAddress, "\177ELF", 4) == 0; }
        inline bool contains(uintptr_t address) const { return address >= startAddress && address < endAddress; }
        inline std::string toString()
        {
          return KittyUtils::String::Fmt("%llx-%llx %c%c%c%c %llx %s %lu %s",
              startAddress, endAddress,
              readable ? 'r' : '-', writeable ? 'w' : '-', executable ? 'x' : '-', is_private ? 'p' : 's',
              offset, dev.c_str(), inode, pathname.c_str());
        }
    };
    bool memWrite(void *address, const void *buffer, size_t len);
    std::string getProcessName();
    std::vector<ProcMap> getAllMaps();
    std::vector<ProcMap> getMapsEqual(const std::vector<ProcMap> &maps, const std::string& name);
    std::vector<ProcMap> getMapsContain(const std::vector<ProcMap> &maps, const std::string& name);
    std::vector<ProcMap> getMapsEndWith(const std::vector<ProcMap> &maps, const std::string& name);
    ProcMap getAddressMap(const std::vector<ProcMap> &maps, const void *address);
    inline std::vector<ProcMap> getMapsEqual(const std::string& name) { return getMapsEqual(getAllMaps(), name); }
    inline std::vector<ProcMap> getMapsContain(const std::string& name) { return getMapsContain(getAllMaps(), name); }
    inline std::vector<ProcMap> getMapsEndWith(const std::string& name) { return getMapsEndWith(getAllMaps(), name); }
    inline ProcMap getAddressMap(const void *address) { return getAddressMap(getAllMaps(), address); }
    ProcMap getElfBaseMap(const std::string& name);
#elif __APPLE__
    enum Memory_Status {
      KMS_FAILED = 0,
      KMS_SUCCESS,
      KMS_INV_ADDR,
      KMS_INV_LEN,
      KMS_INV_BUF,
      KMS_ERR_PROT,
      KMS_ERR_GET_PAGEINFO,
      KMS_ERR_MMAP,
      KMS_ERR_REMAP,
      KMS_ERR_VMCOPY,
    };
    struct seg_data_t {
      uintptr_t start, end;
      unsigned long size;
      seg_data_t() : start(0), end(0), size(0) {}
    };
    class MemoryFileInfo {
    public:
      uint32_t index;
#ifdef __LP64__
      const mach_header_64 *header;
#else
      const mach_header *header;
#endif
      const char *name;
      intptr_t address;
      MemoryFileInfo() : index(0), header(nullptr), name(nullptr), address(0) {}
      inline seg_data_t getSegment(const char *seg_name) const
      {
        seg_data_t data {};
        if (!header || !seg_name) return data;
        data.start = uintptr_t(getsegmentdata(header, seg_name, &data.size));
        data.end = data.start + data.size;
        return data;
      }
      inline seg_data_t getSection(const char *seg_name, const char *sect_name) const
      {
        seg_data_t data {};
        if (!header || !seg_name || !sect_name) return data;
        data.start = uintptr_t(getsectiondata(header, seg_name, sect_name, &data.size));
        data.end = data.start + data.size;
        return data;
      }
    };
    Memory_Status memWrite(void *address, const void *buffer, size_t len);
    kern_return_t getPageInfo(void *page_start, vm_region_submap_short_info_64 *info_out);
    MemoryFileInfo getBaseInfo();
    MemoryFileInfo getMemoryFileInfo(const std::string& fileName);
    uintptr_t getAbsoluteAddress(const char *fileName, uintptr_t address);
#endif
}
