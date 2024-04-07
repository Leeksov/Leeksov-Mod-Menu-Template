#ifndef KEYSTONE_ENGINE_H
#define KEYSTONE_ENGINE_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#ifdef _MSC_VER
#pragma warning(disable:4201)
#pragma warning(disable:4100)
#ifndef KEYSTONE_STATIC
#define KEYSTONE_EXPORT __declspec(dllexport)
#else
#define KEYSTONE_EXPORT
#endif
#else
#ifdef __GNUC__
#include <stdbool.h>
#ifndef KEYSTONE_STATIC
#define KEYSTONE_EXPORT __attribute__((visibility("default")))
#else
#define KEYSTONE_EXPORT
#endif
#else
#define KEYSTONE_EXPORT
#endif
#endif
struct ks_struct;
typedef struct ks_struct ks_engine;
#define KS_API_MAJOR 0
#define KS_API_MINOR 9
#define KS_VERSION_MAJOR KS_API_MAJOR
#define KS_VERSION_MINOR KS_API_MINOR
#define KS_VERSION_EXTRA 2
#define KS_MAKE_VERSION(major, minor) ((major << 8) + minor)
typedef enum ks_arch {
    KS_ARCH_ARM = 1,
    KS_ARCH_ARM64,
    KS_ARCH_MIPS,
    KS_ARCH_X86,
    KS_ARCH_PPC,
    KS_ARCH_SPARC,
    KS_ARCH_SYSTEMZ,
    KS_ARCH_HEXAGON,
    KS_ARCH_EVM,
    KS_ARCH_RISCV,
    KS_ARCH_MAX,
} ks_arch;
typedef enum ks_mode {
    KS_MODE_LITTLE_ENDIAN = 0,
    KS_MODE_ARM = 1 << 0,
    KS_MODE_THUMB = 1 << 4,
    KS_MODE_V8 = 1 << 6,
    KS_MODE_MICRO = 1 << 4,
    KS_MODE_MIPS3 = 1 << 5,
    KS_MODE_MIPS32R6 = 1 << 6,
    KS_MODE_MIPS32 = 1 << 2,
    KS_MODE_MIPS64 = 1 << 3,
    KS_MODE_16 = 1 << 1,
    KS_MODE_32 = 1 << 2,
    KS_MODE_64 = 1 << 3,
    KS_MODE_PPC32 = 1 << 2,
    KS_MODE_PPC64 = 1 << 3,
    KS_MODE_QPX = 1 << 4,
    KS_MODE_RISCV32 = 1 << 2,
    KS_MODE_RISCV64 = 1 << 3,
    KS_MODE_SPARC32 = 1 << 2,
    KS_MODE_SPARC64 = 1 << 3,
    KS_MODE_V9 = 1 << 4,
} ks_mode;
#define KS_ERR_ASM 128
#define KS_ERR_ASM_ARCH 512
typedef enum ks_err {
    KS_ERR_OK = 0,
    KS_ERR_NOMEM,
    KS_ERR_ARCH,
    KS_ERR_HANDLE,
    KS_ERR_MODE,
    KS_ERR_VERSION,
    KS_ERR_OPT_INVALID,
    KS_ERR_ASM_EXPR_TOKEN = KS_ERR_ASM,
    KS_ERR_ASM_DIRECTIVE_VALUE_RANGE,
    KS_ERR_ASM_DIRECTIVE_ID,
    KS_ERR_ASM_DIRECTIVE_TOKEN,
    KS_ERR_ASM_DIRECTIVE_STR,
    KS_ERR_ASM_DIRECTIVE_COMMA,
    KS_ERR_ASM_DIRECTIVE_RELOC_NAME,
    KS_ERR_ASM_DIRECTIVE_RELOC_TOKEN,
    KS_ERR_ASM_DIRECTIVE_FPOINT,
    KS_ERR_ASM_DIRECTIVE_UNKNOWN,
    KS_ERR_ASM_DIRECTIVE_EQU,
    KS_ERR_ASM_DIRECTIVE_INVALID,
    KS_ERR_ASM_VARIANT_INVALID,
    KS_ERR_ASM_EXPR_BRACKET,
    KS_ERR_ASM_SYMBOL_MODIFIER,
    KS_ERR_ASM_SYMBOL_REDEFINED,
    KS_ERR_ASM_SYMBOL_MISSING,
    KS_ERR_ASM_RPAREN,
    KS_ERR_ASM_STAT_TOKEN,
    KS_ERR_ASM_UNSUPPORTED,
    KS_ERR_ASM_MACRO_TOKEN,
    KS_ERR_ASM_MACRO_PAREN,
    KS_ERR_ASM_MACRO_EQU,
    KS_ERR_ASM_MACRO_ARGS,
    KS_ERR_ASM_MACRO_LEVELS_EXCEED,
    KS_ERR_ASM_MACRO_STR,
    KS_ERR_ASM_MACRO_INVALID,
    KS_ERR_ASM_ESC_BACKSLASH,
    KS_ERR_ASM_ESC_OCTAL,
    KS_ERR_ASM_ESC_SEQUENCE,
    KS_ERR_ASM_ESC_STR,
    KS_ERR_ASM_TOKEN_INVALID,
    KS_ERR_ASM_INSN_UNSUPPORTED,
    KS_ERR_ASM_FIXUP_INVALID,
    KS_ERR_ASM_LABEL_INVALID,
    KS_ERR_ASM_FRAGMENT_INVALID,
    KS_ERR_ASM_INVALIDOPERAND = KS_ERR_ASM_ARCH,
    KS_ERR_ASM_MISSINGFEATURE,
    KS_ERR_ASM_MNEMONICFAIL,
} ks_err;
typedef bool (*ks_sym_resolver)(const char *symbol, uint64_t *value);
typedef enum ks_opt_type {
	KS_OPT_SYNTAX = 1,
	KS_OPT_SYM_RESOLVER,
} ks_opt_type;
typedef enum ks_opt_value {
	KS_OPT_SYNTAX_INTEL =   1 << 0,
	KS_OPT_SYNTAX_ATT   =   1 << 1,
	KS_OPT_SYNTAX_NASM  =   1 << 2,
	KS_OPT_SYNTAX_MASM  =   1 << 3,
	KS_OPT_SYNTAX_GAS   =   1 << 4,
	KS_OPT_SYNTAX_RADIX16 = 1 << 5,
} ks_opt_value;
#include "arm64.h"
KEYSTONE_EXPORT
unsigned int ks_version(unsigned int *major, unsigned int *minor);
KEYSTONE_EXPORT
bool ks_arch_supported(ks_arch arch);
KEYSTONE_EXPORT
ks_err ks_open(ks_arch arch, int mode, ks_engine **ks);
KEYSTONE_EXPORT
ks_err ks_close(ks_engine *ks);
KEYSTONE_EXPORT
ks_err ks_errno(ks_engine *ks);
KEYSTONE_EXPORT
const char *ks_strerror(ks_err code);
KEYSTONE_EXPORT
ks_err ks_option(ks_engine *ks, ks_opt_type type, size_t value);
KEYSTONE_EXPORT
int ks_asm(ks_engine *ks,
        const char *string,
        uint64_t address,
        unsigned char **encoding, size_t *encoding_size,
        size_t *stat_count);
KEYSTONE_EXPORT
void ks_free(unsigned char *p);
#ifdef __cplusplus
}
#endif
#endif