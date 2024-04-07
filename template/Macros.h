#include "Menu.h"
#import "Obfuscate.h"
#import "KittyMemory/writeData.hpp"
#include <substrate.h>
#include <mach-o/dyld.h>
extern Menu *menu;
extern Switches *switches;
#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^
#define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)
#define HOOK_NO_ORIG(offset, ptr) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, NULL)
#define HOOKSYM(sym, ptr, org) MSHookFunction((void*)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, (void **)&org)
#define HOOKSYM_NO_ORIG(sym, ptr)  MSHookFunction((void*)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, NULL)
#define getSym(symName) dlsym((void *)RTLD_DEFAULT, symName)
#define UIColorFromHex(hexColor) [UIColor colorWithRed:((float)((hexColor & 0xFF0000) >> 16))/255.0 green:((float)((hexColor & 0xFF00) >> 8))/255.0 blue:((float)(hexColor & 0xFF))/255.0 alpha:1.0]
uint64_t getRealOffset(uint64_t offset){
	return KittyMemory::getAbsoluteAddress([menu getFrameworkName], offset);
}
void patchOffset(uint64_t offset, std::string hexBytes) {
	MemoryPatch patch = MemoryPatch::createWithHex([menu getFrameworkName], offset, hexBytes);
	if(!patch.isValid()){
		[menu showPopup:@"Invalid patch" description:[NSString stringWithFormat:@"Failing offset: 0x%llu, please re-check the hex you entered.", offset]];
		return;
	}
	if(!patch.Modify()) {
      [menu showPopup:@"Something went wrong!" description:[NSString stringWithFormat:@"Something went wrong while patching this offset: 0x%llu", offset]];
    }
}