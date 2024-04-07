#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <utility>
#include "KittyMemory.hpp"
namespace KittyScanner
{
    std::vector<uintptr_t> findBytesAll(const uintptr_t start, const uintptr_t end, const char *bytes, const std::string& mask);
     uintptr_t findBytesFirst(const uintptr_t start, const uintptr_t end, const char *bytes, const std::string& mask);
    std::vector<uintptr_t> findHexAll(const uintptr_t start, const uintptr_t end, std::string hex, const std::string& mask);
    uintptr_t findHexFirst(const uintptr_t start, const uintptr_t end, std::string hex, const std::string& mask);
    std::vector<uintptr_t> findIdaPatternAll(const uintptr_t start, const uintptr_t end, const std::string& pattern);
    uintptr_t findIdaPatternFirst(const uintptr_t start, const uintptr_t end, const std::string& pattern);
    std::vector<uintptr_t> findDataAll(const uintptr_t start, const uintptr_t end, const void *data, size_t size);
    uintptr_t findDataFirst(const uintptr_t start, const uintptr_t end, const void *data, size_t size);
#ifdef __ANDROID__
    class RegisterNativeFn
    {
    public:
        char *name;
        char *signature;
        void *fnPtr;
        RegisterNativeFn() : name(nullptr), signature(nullptr), fnPtr(nullptr) {}
        inline bool isValid() const { return (name != nullptr && signature != nullptr && fnPtr != nullptr); }
    };
    RegisterNativeFn findRegisterNativeFn(const class ElfScanner &elf, const std::string &name);
    class ElfScanner
    {
    private:
        uintptr_t _elfBase;
        ElfW_(Ehdr) _ehdr;
        uintptr_t _phdr;
        std::vector<ElfW_(Phdr)> _phdrs;
        int _loads;
        uintptr_t _loadBias, _loadSize;
        uintptr_t _bss;
        size_t _bssSize;
        uintptr_t _dynamic;
        std::vector<ElfW_(Dyn)> _dynamics;
        uintptr_t _stringTable, _symbolTable, _elfHashTable, _gnuHashTable;
        size_t _strsz, _syment;
        KittyMemory::ProcMap _base_segment;
        std::vector<KittyMemory::ProcMap> _segments;
    public:
        ElfScanner()
            : _elfBase(0)
            , _phdr(0)
            , _loads(0)
            , _loadBias(0)
            , _loadSize(0)
            , _bss(0)
            , _bssSize(0)
            , _dynamic(0)
            , _stringTable(0)
            , _symbolTable(0)
            , _elfHashTable(0)
            , _gnuHashTable(0)
            , _strsz(0)
            , _syment(0)
        {
        }
        ElfScanner(uintptr_t elfBase, const std::vector<KittyMemory::ProcMap> &maps);      
        ElfScanner(uintptr_t elfBase) : ElfScanner(elfBase, KittyMemory::getAllMaps()) {}
        static inline ElfScanner createWithBase(uintptr_t elfBase)
        {
            return ElfScanner(elfBase);
        }
        static inline ElfScanner createWithMap(const KittyMemory::ProcMap& map)
        {
            return ElfScanner(map.startAddress);
        }
        static inline ElfScanner createWithPath(const std::string &path)
        {
            return ElfScanner(KittyMemory::getElfBaseMap(path).startAddress);
        }

        inline bool isValid() const
        {
            return _loads && !_phdrs.empty() && _loadBias && _loadSize && !_dynamics.empty() && _stringTable && _symbolTable && _strsz && _syment;
        }
        inline uintptr_t base() const { return _elfBase; }
        inline uintptr_t end() const { return _elfBase + _loadSize; }
        inline ElfW_(Ehdr) header() const { return _ehdr; }
        inline uintptr_t phdr() const { return _phdr; }
        inline std::vector<ElfW_(Phdr)> programHeaders() const { return _phdrs; }
        inline int loads() const { return _loads; }
        inline uintptr_t loadBias() const { return _loadBias; }
        inline uintptr_t loadSize() const { return _loadSize; }
        inline uintptr_t bss() const { return _bss; }
        inline size_t bssSize() const { return _bssSize; }
        inline uintptr_t dynamic() const { return _dynamic; }
        inline std::vector<ElfW_(Dyn)> dynamics() const { return _dynamics; }
        inline uintptr_t stringTable() const { return _stringTable; }
        inline uintptr_t symbolTable() const { return _symbolTable; }
        inline uintptr_t elfHashTable() const { return _elfHashTable; }
        inline uintptr_t gnuHashTable() const { return _gnuHashTable; }
        inline size_t stringTableSize() const { return _strsz; }
        inline size_t symbolEntrySize() const { return _syment; }
        uintptr_t findSymbol(const std::string& symbolName) const;
        inline KittyMemory::ProcMap baseSegment() const { return _base_segment; }
        inline std::vector<KittyMemory::ProcMap> segments() const { return _segments; }
        inline std::string filePath() const { return _base_segment.pathname; }
        static std::vector<ElfScanner> getAllELFs();
        static std::vector<std::pair<uintptr_t, ElfScanner>> findSymbolAll(const std::string& symbolName);
    };
#endif
}