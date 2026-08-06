#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif /* PY_SSIZE_T_CLEAN */
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03030000)
    #error Cython requires Python 2.6+ or Python 3.3+.
#else
#define CYTHON_ABI "0_29_37"
#define CYTHON_HEX_VERSION 0x001D25F0
#define CYTHON_FUTURE_DIVISION 0
#include <stddef.h>
#ifndef offsetof
  #define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#define __PYX_COMMA ,
#ifndef HAVE_LONG_LONG
  #if PY_VERSION_HEX >= 0x02070000
    #define HAVE_LONG_LONG
  #endif
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
  #define CYTHON_COMPILING_IN_PYPY 1
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #define CYTHON_COMPILING_IN_NOGIL 0
  #undef CYTHON_USE_TYPE_SLOTS
  #define CYTHON_USE_TYPE_SLOTS 0
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #if PY_VERSION_HEX < 0x03050000
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #undef CYTHON_USE_UNICODE_INTERNALS
  #define CYTHON_USE_UNICODE_INTERNALS 0
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #undef CYTHON_AVOID_BORROWED_REFS
  #define CYTHON_AVOID_BORROWED_REFS 1
  #undef CYTHON_ASSUME_SAFE_MACROS
  #define CYTHON_ASSUME_SAFE_MACROS 0
  #undef CYTHON_UNPACK_METHODS
  #define CYTHON_UNPACK_METHODS 0
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #if PY_VERSION_HEX < 0x03090000
    #undef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT 0
  #elif !defined(CYTHON_PEP489_MULTI_PHASE_INIT)
    #define CYTHON_PEP489_MULTI_PHASE_INIT 1
  #endif
  #undef CYTHON_USE_TP_FINALIZE
  #define CYTHON_USE_TP_FINALIZE (PY_VERSION_HEX >= 0x030400a1 && PYPY_VERSION_NUM >= 0x07030C00)
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
  #ifndef CYTHON_UPDATE_DESCRIPTOR_DOC
    #define CYTHON_UPDATE_DESCRIPTOR_DOC 0
  #endif
#elif defined(PYSTON_VERSION)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 1
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #define CYTHON_COMPILING_IN_NOGIL 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #undef CYTHON_PEP489_MULTI_PHASE_INIT
  #define CYTHON_PEP489_MULTI_PHASE_INIT 0
  #undef CYTHON_USE_TP_FINALIZE
  #define CYTHON_USE_TP_FINALIZE 0
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
  #ifndef CYTHON_UPDATE_DESCRIPTOR_DOC
    #define CYTHON_UPDATE_DESCRIPTOR_DOC 0
  #endif
#elif defined(PY_NOGIL)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #define CYTHON_COMPILING_IN_NOGIL 1
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #ifndef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #ifndef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT 1
  #endif
  #ifndef CYTHON_USE_TP_FINALIZE
    #define CYTHON_USE_TP_FINALIZE 1
  #endif
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
#else
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 1
  #define CYTHON_COMPILING_IN_NOGIL 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYTYPE_LOOKUP
    #define CYTHON_USE_PYTYPE_LOOKUP 0
  #elif !defined(CYTHON_USE_PYTYPE_LOOKUP)
    #define CYTHON_USE_PYTYPE_LOOKUP 1
  #endif
  #if PY_MAJOR_VERSION < 3
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYLONG_INTERNALS
    #define CYTHON_USE_PYLONG_INTERNALS 0
  #elif !defined(CYTHON_USE_PYLONG_INTERNALS)
    #define CYTHON_USE_PYLONG_INTERNALS (PY_VERSION_HEX < 0x030C00A5)
  #endif
  #ifndef CYTHON_USE_PYLIST_INTERNALS
    #define CYTHON_USE_PYLIST_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #if PY_VERSION_HEX < 0x030300F0 || PY_VERSION_HEX >= 0x030B00A2
    #undef CYTHON_USE_UNICODE_WRITER
    #define CYTHON_USE_UNICODE_WRITER 0
  #elif !defined(CYTHON_USE_UNICODE_WRITER)
    #define CYTHON_USE_UNICODE_WRITER 1
  #endif
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #if PY_VERSION_HEX >= 0x030B00A4
    #undef CYTHON_FAST_THREAD_STATE
    #define CYTHON_FAST_THREAD_STATE 0
  #elif !defined(CYTHON_FAST_THREAD_STATE)
    #define CYTHON_FAST_THREAD_STATE 1
  #endif
  #ifndef CYTHON_FAST_PYCALL
    #define CYTHON_FAST_PYCALL (PY_VERSION_HEX < 0x030A0000)
  #endif
  #ifndef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT (PY_VERSION_HEX >= 0x03050000)
  #endif
  #ifndef CYTHON_USE_TP_FINALIZE
    #define CYTHON_USE_TP_FINALIZE (PY_VERSION_HEX >= 0x030400a1)
  #endif
  #ifndef CYTHON_USE_DICT_VERSIONS
    #define CYTHON_USE_DICT_VERSIONS ((PY_VERSION_HEX >= 0x030600B1) && (PY_VERSION_HEX < 0x030C00A5))
  #endif
  #if PY_VERSION_HEX >= 0x030B00A4
    #undef CYTHON_USE_EXC_INFO_STACK
    #define CYTHON_USE_EXC_INFO_STACK 0
  #elif !defined(CYTHON_USE_EXC_INFO_STACK)
    #define CYTHON_USE_EXC_INFO_STACK (PY_VERSION_HEX >= 0x030700A3)
  #endif
  #ifndef CYTHON_UPDATE_DESCRIPTOR_DOC
    #define CYTHON_UPDATE_DESCRIPTOR_DOC 1
  #endif
#endif
#if !defined(CYTHON_FAST_PYCCALL)
#define CYTHON_FAST_PYCCALL  (CYTHON_FAST_PYCALL && PY_VERSION_HEX >= 0x030600B1)
#endif
#if CYTHON_USE_PYLONG_INTERNALS
  #if PY_MAJOR_VERSION < 3
    #include "longintrepr.h"
  #endif
  #undef SHIFT
  #undef BASE
  #undef MASK
  #ifdef SIZEOF_VOID_P
    enum { __pyx_check_sizeof_voidp = 1 / (int)(SIZEOF_VOID_P == sizeof(void*)) };
  #endif
#endif
#ifndef __has_attribute
  #define __has_attribute(x) 0
#endif
#ifndef __has_cpp_attribute
  #define __has_cpp_attribute(x) 0
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_MAYBE_UNUSED_VAR
#  if defined(__cplusplus)
     template<class T> void CYTHON_MAYBE_UNUSED_VAR( const T& ) { }
#  else
#    define CYTHON_MAYBE_UNUSED_VAR(x) (void)(x)
#  endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
#define __Pyx_void_to_None(void_result) ((void)(void_result), Py_INCREF(Py_None), Py_None)
#ifdef _MSC_VER
    #ifndef _MSC_STDINT_H_
        #if _MSC_VER < 1300
           typedef unsigned char     uint8_t;
           typedef unsigned int      uint32_t;
        #else
           typedef unsigned __int8   uint8_t;
           typedef unsigned __int32  uint32_t;
        #endif
    #endif
#else
   #include <stdint.h>
#endif
#ifndef CYTHON_FALLTHROUGH
  #if defined(__cplusplus) && __cplusplus >= 201103L
    #if __has_cpp_attribute(fallthrough)
      #define CYTHON_FALLTHROUGH [[fallthrough]]
    #elif __has_cpp_attribute(clang::fallthrough)
      #define CYTHON_FALLTHROUGH [[clang::fallthrough]]
    #elif __has_cpp_attribute(gnu::fallthrough)
      #define CYTHON_FALLTHROUGH [[gnu::fallthrough]]
    #endif
  #endif
  #ifndef CYTHON_FALLTHROUGH
    #if __has_attribute(fallthrough)
      #define CYTHON_FALLTHROUGH __attribute__((fallthrough))
    #else
      #define CYTHON_FALLTHROUGH
    #endif
  #endif
  #if defined(__clang__ ) && defined(__apple_build_version__)
    #if __apple_build_version__ < 7000000
      #undef  CYTHON_FALLTHROUGH
      #define CYTHON_FALLTHROUGH
    #endif
  #endif
#endif

#ifndef CYTHON_INLINE
  #if defined(__clang__)
    #define CYTHON_INLINE __inline__ __attribute__ ((__unused__))
  #elif defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif

#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_DefaultClassType PyType_Type
#if PY_VERSION_HEX >= 0x030B00A1
    static CYTHON_INLINE PyCodeObject* __Pyx_PyCode_New(int a, int k, int l, int s, int f,
                                                    PyObject *code, PyObject *c, PyObject* n, PyObject *v,
                                                    PyObject *fv, PyObject *cell, PyObject* fn,
                                                    PyObject *name, int fline, PyObject *lnos) {
        PyObject *kwds=NULL, *argcount=NULL, *posonlyargcount=NULL, *kwonlyargcount=NULL;
        PyObject *nlocals=NULL, *stacksize=NULL, *flags=NULL, *replace=NULL, *call_result=NULL, *empty=NULL;
        const char *fn_cstr=NULL;
        const char *name_cstr=NULL;
        PyCodeObject* co=NULL;
        PyObject *type, *value, *traceback;
        PyErr_Fetch(&type, &value, &traceback);
        if (!(kwds=PyDict_New())) goto end;
        if (!(argcount=PyLong_FromLong(a))) goto end;
        if (PyDict_SetItemString(kwds, "co_argcount", argcount) != 0) goto end;
        if (!(posonlyargcount=PyLong_FromLong(0))) goto end;
        if (PyDict_SetItemString(kwds, "co_posonlyargcount", posonlyargcount) != 0) goto end;
        if (!(kwonlyargcount=PyLong_FromLong(k))) goto end;
        if (PyDict_SetItemString(kwds, "co_kwonlyargcount", kwonlyargcount) != 0) goto end;
        if (!(nlocals=PyLong_FromLong(l))) goto end;
        if (PyDict_SetItemString(kwds, "co_nlocals", nlocals) != 0) goto end;
        if (!(stacksize=PyLong_FromLong(s))) goto end;
        if (PyDict_SetItemString(kwds, "co_stacksize", stacksize) != 0) goto end;
        if (!(flags=PyLong_FromLong(f))) goto end;
        if (PyDict_SetItemString(kwds, "co_flags", flags) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_code", code) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_consts", c) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_names", n) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_varnames", v) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_freevars", fv) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_cellvars", cell) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_linetable", lnos) != 0) goto end;
        if (!(fn_cstr=PyUnicode_AsUTF8AndSize(fn, NULL))) goto end;
        if (!(name_cstr=PyUnicode_AsUTF8AndSize(name, NULL))) goto end;
        if (!(co = PyCode_NewEmpty(fn_cstr, name_cstr, fline))) goto end;
        if (!(replace = PyObject_GetAttrString((PyObject*)co, "replace"))) goto cleanup_code_too;
        if (!(empty = PyTuple_New(0))) goto cleanup_code_too; // unfortunately __pyx_empty_tuple isn't available here
        if (!(call_result = PyObject_Call(replace, empty, kwds))) goto cleanup_code_too;
        Py_XDECREF((PyObject*)co);
        co = (PyCodeObject*)call_result;
        call_result = NULL;
        if (0) {
            cleanup_code_too:
            Py_XDECREF((PyObject*)co);
            co = NULL;
        }
        end:
        Py_XDECREF(kwds);
        Py_XDECREF(argcount);
        Py_XDECREF(posonlyargcount);
        Py_XDECREF(kwonlyargcount);
        Py_XDECREF(nlocals);
        Py_XDECREF(stacksize);
        Py_XDECREF(replace);
        Py_XDECREF(call_result);
        Py_XDECREF(empty);
        if (type) {
            PyErr_Restore(type, value, traceback);
        }
        return co;
    }
#else
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#endif
  #define __Pyx_DefaultClassType PyType_Type
#endif
#if PY_VERSION_HEX >= 0x030900F0 && !CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyObject_GC_IsFinalized(o) PyObject_GC_IsFinalized(o)
#else
  #define __Pyx_PyObject_GC_IsFinalized(o) _PyGC_FINALIZED(o)
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#ifndef METH_STACKLESS
  #define METH_STACKLESS 0
#endif
#if PY_VERSION_HEX <= 0x030700A3 || !defined(METH_FASTCALL)
  #ifndef METH_FASTCALL
     #define METH_FASTCALL 0x80
  #endif
  typedef PyObject *(*__Pyx_PyCFunctionFast) (PyObject *self, PyObject *const *args, Py_ssize_t nargs);
  typedef PyObject *(*__Pyx_PyCFunctionFastWithKeywords) (PyObject *self, PyObject *const *args,
                                                          Py_ssize_t nargs, PyObject *kwnames);
#else
  #define __Pyx_PyCFunctionFast _PyCFunctionFast
  #define __Pyx_PyCFunctionFastWithKeywords _PyCFunctionFastWithKeywords
#endif
#if CYTHON_FAST_PYCCALL
#define __Pyx_PyFastCFunction_Check(func)\
    ((PyCFunction_Check(func) && (METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS | METH_STACKLESS)))))
#else
#define __Pyx_PyFastCFunction_Check(func) 0
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
  #define PyObject_Malloc(s)   PyMem_Malloc(s)
  #define PyObject_Free(p)     PyMem_Free(p)
  #define PyObject_Realloc(p)  PyMem_Realloc(p)
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX < 0x030400A1
  #define PyMem_RawMalloc(n)           PyMem_Malloc(n)
  #define PyMem_RawRealloc(p, n)       PyMem_Realloc(p, n)
  #define PyMem_RawFree(p)             PyMem_Free(p)
#endif
#if CYTHON_COMPILING_IN_PYSTON
  #define __Pyx_PyCode_HasFreeVars(co)  PyCode_HasFreeVars(co)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno) PyFrame_SetLineNumber(frame, lineno)
#else
  #define __Pyx_PyCode_HasFreeVars(co)  (PyCode_GetNumFree(co) > 0)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno)  (frame)->f_lineno = (lineno)
#endif
#if !CYTHON_FAST_THREAD_STATE || PY_VERSION_HEX < 0x02070000
  #define __Pyx_PyThreadState_Current PyThreadState_GET()
#elif PY_VERSION_HEX >= 0x03060000
  #define __Pyx_PyThreadState_Current _PyThreadState_UncheckedGet()
#elif PY_VERSION_HEX >= 0x03000000
  #define __Pyx_PyThreadState_Current PyThreadState_GET()
#else
  #define __Pyx_PyThreadState_Current _PyThreadState_Current
#endif
#if PY_VERSION_HEX < 0x030700A2 && !defined(PyThread_tss_create) && !defined(Py_tss_NEEDS_INIT)
#include "pythread.h"
#define Py_tss_NEEDS_INIT 0
typedef int Py_tss_t;
static CYTHON_INLINE int PyThread_tss_create(Py_tss_t *key) {
  *key = PyThread_create_key();
  return 0;
}
static CYTHON_INLINE Py_tss_t * PyThread_tss_alloc(void) {
  Py_tss_t *key = (Py_tss_t *)PyObject_Malloc(sizeof(Py_tss_t));
  *key = Py_tss_NEEDS_INIT;
  return key;
}
static CYTHON_INLINE void PyThread_tss_free(Py_tss_t *key) {
  PyObject_Free(key);
}
static CYTHON_INLINE int PyThread_tss_is_created(Py_tss_t *key) {
  return *key != Py_tss_NEEDS_INIT;
}
static CYTHON_INLINE void PyThread_tss_delete(Py_tss_t *key) {
  PyThread_delete_key(*key);
  *key = Py_tss_NEEDS_INIT;
}
static CYTHON_INLINE int PyThread_tss_set(Py_tss_t *key, void *value) {
  return PyThread_set_key_value(*key, value);
}
static CYTHON_INLINE void * PyThread_tss_get(Py_tss_t *key) {
  return PyThread_get_key_value(*key);
}
#endif
#if CYTHON_COMPILING_IN_CPYTHON || defined(_PyDict_NewPresized)
#define __Pyx_PyDict_NewPresized(n)  ((n <= 8) ? PyDict_New() : _PyDict_NewPresized(n))
#else
#define __Pyx_PyDict_NewPresized(n)  PyDict_New()
#endif
#if PY_MAJOR_VERSION >= 3 || CYTHON_FUTURE_DIVISION
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030500A1 && CYTHON_USE_UNICODE_INTERNALS
#define __Pyx_PyDict_GetItemStr(dict, name)  _PyDict_GetItem_KnownHash(dict, name, ((PyASCIIObject *) name)->hash)
#else
#define __Pyx_PyDict_GetItemStr(dict, name)  PyDict_GetItem(dict, name)
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #if PY_VERSION_HEX >= 0x030C0000
    #define __Pyx_PyUnicode_READY(op)       (0)
  #else
    #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ?\
                                                0 : _PyUnicode_Ready((PyObject *)(op)))
  #endif
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   PyUnicode_MAX_CHAR_VALUE(u)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  PyUnicode_WRITE(k, d, i, ch)
  #if PY_VERSION_HEX >= 0x030C0000
    #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_LENGTH(u))
  #else
    #if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x03090000
    #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : ((PyCompactUnicodeObject *)(u))->wstr_length))
    #else
    #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : PyUnicode_GET_SIZE(u)))
    #endif
  #endif
#else
  #define CYTHON_PEP393_ENABLED 0
  #define PyUnicode_1BYTE_KIND  1
  #define PyUnicode_2BYTE_KIND  2
  #define PyUnicode_4BYTE_KIND  4
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   ((sizeof(Py_UNICODE) == 2) ? 65535 : 1114111)
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  (((void)(k)), ((Py_UNICODE*)d)[i] = ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_SIZE(u))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ?\
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
  #define PyByteArray_Check(obj)  PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Format)
  #define PyObject_Format(obj, fmt)  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None || (PyString_Check(b) && !PyString_CheckExact(b)))) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None || (PyUnicode_Check(b) && !PyUnicode_CheckExact(b)))) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
  #define PyObject_ASCII(o)            PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#ifndef PyObject_Unicode
  #define PyObject_Unicode             PyObject_Str
#endif
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#if PY_VERSION_HEX >= 0x030900A4
  #define __Pyx_SET_REFCNT(obj, refcnt) Py_SET_REFCNT(obj, refcnt)
  #define __Pyx_SET_SIZE(obj, size) Py_SET_SIZE(obj, size)
#else
  #define __Pyx_SET_REFCNT(obj, refcnt) Py_REFCNT(obj) = (refcnt)
  #define __Pyx_SET_SIZE(obj, size) Py_SIZE(obj) = (size)
#endif
#if CYTHON_ASSUME_SAFE_MACROS
  #define __Pyx_PySequence_SIZE(seq)  Py_SIZE(seq)
#else
  #define __Pyx_PySequence_SIZE(seq)  PySequence_Size(seq)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   __Pyx_PyIndex_AsHash_t
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   __Pyx_PyIndex_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? ((void)(klass), PyMethod_New(func, self)) : __Pyx_NewRef(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#if CYTHON_USE_ASYNC_SLOTS
  #if PY_VERSION_HEX >= 0x030500B1
    #define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
    #define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
  #else
    #define __Pyx_PyType_AsAsync(obj) ((__Pyx_PyAsyncMethodsStruct*) (Py_TYPE(obj)->tp_reserved))
  #endif
#else
  #define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef __Pyx_PyAsyncMethodsStruct
    typedef struct {
        unaryfunc am_await;
        unaryfunc am_aiter;
        unaryfunc am_anext;
    } __Pyx_PyAsyncMethodsStruct;
#endif

#if defined(_WIN32) || defined(WIN32) || defined(MS_WINDOWS)
  #if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES
  #endif
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#if defined(__CYGWIN__) && defined(_LDBL_EQ_DBL)
#define __Pyx_truncl trunc
#else
#define __Pyx_truncl truncl
#endif

#define __PYX_MARK_ERR_POS(f_index, lineno) \
    { __pyx_filename = __pyx_f[f_index]; (void)__pyx_filename; __pyx_lineno = lineno; (void)__pyx_lineno; __pyx_clineno = __LINE__; (void)__pyx_clineno; }
#define __PYX_ERR(f_index, lineno, Ln_error) \
    { __PYX_MARK_ERR_POS(f_index, lineno) goto Ln_error; }

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#define __PYX_HAVE__HP
#define __PYX_HAVE_API__HP
/* Early includes */
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#if defined(PYREX_WITHOUT_ASSERTIONS) && !defined(CYTHON_WITHOUT_ASSERTIONS)
#define CYTHON_WITHOUT_ASSERTIONS
#endif

typedef struct {PyObject **p; const char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_UTF8 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT (PY_MAJOR_VERSION >= 3 && __PYX_DEFAULT_STRING_ENCODING_IS_UTF8)
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (\
    (sizeof(type) < sizeof(Py_ssize_t))  ||\
    (sizeof(type) > sizeof(Py_ssize_t) &&\
          likely(v < (type)PY_SSIZE_T_MAX ||\
                 v == (type)PY_SSIZE_T_MAX)  &&\
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||\
                                v == (type)PY_SSIZE_T_MIN)))  ||\
    (sizeof(type) == sizeof(Py_ssize_t) &&\
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||\
                               v == (type)PY_SSIZE_T_MAX)))  )
static CYTHON_INLINE int __Pyx_is_valid_index(Py_ssize_t i, Py_ssize_t limit) {
    return (size_t) i < (size_t) limit;
}
#if defined (__cplusplus) && __cplusplus >= 201103L
    #include <cstdlib>
    #define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) labs(value)
#elif defined (_MSC_VER)
    #define __Pyx_sst_abs(value) ((Py_ssize_t)_abs64(value))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define __Pyx_sst_abs(value) llabs(value)
#elif defined (__GNUC__)
    #define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
    #define __Pyx_sst_abs(value) ((value<0) ? -value : value)
#endif
static CYTHON_INLINE const char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE const char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyBytes_AsWritableString(s)     ((char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsWritableSString(s)    ((signed char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsWritableUString(s)    ((unsigned char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsString(s)     ((const char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsSString(s)    ((const signed char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsUString(s)    ((const unsigned char*) PyBytes_AS_STRING(s))
#define __Pyx_PyObject_AsWritableString(s)    ((char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsSString(s)    ((const signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((const unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u) {
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
static CYTHON_INLINE PyObject * __Pyx_PyBool_FromLong(long b);
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE int __Pyx_PyObject_IsTrueAndDecref(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x);
#define __Pyx_PySequence_Tuple(obj)\
    (likely(PyTuple_CheckExact(obj)) ? __Pyx_NewRef(obj) : PySequence_Tuple(obj))
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
static CYTHON_INLINE Py_hash_t __Pyx_PyIndex_AsHash_t(PyObject*);
#if CYTHON_ASSUME_SAFE_MACROS
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c) + 1);
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */
static CYTHON_INLINE void __Pyx_pretend_to_initialize(void* ptr) { (void)ptr; }

static PyObject *__pyx_m = NULL;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_cython_runtime = NULL;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "HP.py",
};

/*--- Type declarations ---*/
struct __pyx_obj_2HP___pyx_scope_struct__sum;
struct __pyx_obj_2HP___pyx_scope_struct_1_genexpr;
struct __pyx_obj_2HP___pyx_scope_struct_2___str__;
struct __pyx_obj_2HP___pyx_scope_struct_3_genexpr;
struct __pyx_obj_2HP___pyx_scope_struct_4___init__;
struct __pyx_obj_2HP___pyx_scope_struct_5__execute_for_loop;

/* "HP.py":97
 *         return len(self.items)
 * 
 *     def sum(self):             # <<<<<<<<<<<<<<
 *         return sum(item for item in self.items if isinstance(item, (int, float)))
 * 
 */
struct __pyx_obj_2HP___pyx_scope_struct__sum {
  PyObject_HEAD
  PyObject *__pyx_v_self;
};


/* "HP.py":98
 * 
 *     def sum(self):
 *         return sum(item for item in self.items if isinstance(item, (int, float)))             # <<<<<<<<<<<<<<
 * 
 *     def avg(self):
 */
struct __pyx_obj_2HP___pyx_scope_struct_1_genexpr {
  PyObject_HEAD
  struct __pyx_obj_2HP___pyx_scope_struct__sum *__pyx_outer_scope;
  PyObject *__pyx_v_item;
  PyObject *__pyx_t_0;
  Py_ssize_t __pyx_t_1;
  PyObject *(*__pyx_t_2)(PyObject *);
};


/* "HP.py":112
 *         return max(nums) if nums else None
 * 
 *     def __str__(self):             # <<<<<<<<<<<<<<
 *         return "[" + ", ".join(str(item) for item in self.items) + "]"
 * 
 */
struct __pyx_obj_2HP___pyx_scope_struct_2___str__ {
  PyObject_HEAD
  PyObject *__pyx_v_self;
};


/* "HP.py":113
 * 
 *     def __str__(self):
 *         return "[" + ", ".join(str(item) for item in self.items) + "]"             # <<<<<<<<<<<<<<
 * 
 *     def __repr__(self):
 */
struct __pyx_obj_2HP___pyx_scope_struct_3_genexpr {
  PyObject_HEAD
  struct __pyx_obj_2HP___pyx_scope_struct_2___str__ *__pyx_outer_scope;
  PyObject *__pyx_v_item;
  PyObject *__pyx_t_0;
  Py_ssize_t __pyx_t_1;
  PyObject *(*__pyx_t_2)(PyObject *);
};


/* "HP.py":300
 *             return line
 * 
 *     def __init__(self):             # <<<<<<<<<<<<<<
 *         self.variables = {}
 *         self.colors = {
 */
struct __pyx_obj_2HP___pyx_scope_struct_4___init__ {
  PyObject_HEAD
  PyObject *__pyx_v_self;
};


/* "HP.py":835
 *         return e
 * 
 *     def _execute_for_loop(self, lines, idx):             # <<<<<<<<<<<<<<
 *         line = lines[idx].strip().replace('{', '').strip()
 *         m = re.match(r'for\s+(\w+)\s*~\s*(.+)', line)
 */
struct __pyx_obj_2HP___pyx_scope_struct_5__execute_for_loop {
  PyObject_HEAD
  PyObject *__pyx_v_e;
  PyObject *__pyx_v_lines;
  PyObject *__pyx_v_s;
  PyObject *__pyx_v_self;
  PyObject *__pyx_v_var;
};


/* --- Runtime support code (head) --- */
/* Refnanny.proto */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          if (acquire_gil) {\
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
              PyGILState_Release(__pyx_gilstate_save);\
          } else {\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext()\
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_XDECREF(tmp);\
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_DECREF(tmp);\
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

/* PyObjectGetAttrStr.proto */
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

/* GetBuiltinName.proto */
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

/* RaiseArgTupleInvalid.proto */
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found);

/* RaiseDoubleKeywords.proto */
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name);

/* ParseKeywords.proto */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],\
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args,\
    const char* function_name);

/* PyObjectSetAttrStr.proto */
#if CYTHON_USE_TYPE_SLOTS
#define __Pyx_PyObject_DelAttrStr(o,n) __Pyx_PyObject_SetAttrStr(o, n, NULL)
static CYTHON_INLINE int __Pyx_PyObject_SetAttrStr(PyObject* obj, PyObject* attr_name, PyObject* value);
#else
#define __Pyx_PyObject_DelAttrStr(o,n)   PyObject_DelAttr(o,n)
#define __Pyx_PyObject_SetAttrStr(o,n,v) PyObject_SetAttr(o,n,v)
#endif

/* PyFloatBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_DivideObjC(PyObject *op1, PyObject *op2, double floatval, int inplace, int zerodivision_check);
#else
#define __Pyx_PyFloat_DivideObjC(op1, op2, floatval, inplace, zerodivision_check)\
    ((inplace ? __Pyx_PyNumber_InPlaceDivide(op1, op2) : __Pyx_PyNumber_Divide(op1, op2)))
    #endif

/* PyObjectFormatSimple.proto */
#if CYTHON_COMPILING_IN_PYPY
    #define __Pyx_PyObject_FormatSimple(s, f) (\
        likely(PyUnicode_CheckExact(s)) ? (Py_INCREF(s), s) :\
        PyObject_Format(s, f))
#elif PY_MAJOR_VERSION < 3
    #define __Pyx_PyObject_FormatSimple(s, f) (\
        likely(PyUnicode_CheckExact(s)) ? (Py_INCREF(s), s) :\
        likely(PyString_CheckExact(s)) ? PyUnicode_FromEncodedObject(s, NULL, "strict") :\
        PyObject_Format(s, f))
#elif CYTHON_USE_TYPE_SLOTS
    #define __Pyx_PyObject_FormatSimple(s, f) (\
        likely(PyUnicode_CheckExact(s)) ? (Py_INCREF(s), s) :\
        likely(PyLong_CheckExact(s)) ? PyLong_Type.tp_str(s) :\
        likely(PyFloat_CheckExact(s)) ? PyFloat_Type.tp_str(s) :\
        PyObject_Format(s, f))
#else
    #define __Pyx_PyObject_FormatSimple(s, f) (\
        likely(PyUnicode_CheckExact(s)) ? (Py_INCREF(s), s) :\
        PyObject_Format(s, f))
#endif

/* PyCFunctionFastCall.proto */
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func, PyObject **args, Py_ssize_t nargs);
#else
#define __Pyx_PyCFunction_FastCall(func, args, nargs)  (assert(0), NULL)
#endif

/* PyFunctionFastCall.proto */
#if CYTHON_FAST_PYCALL
#define __Pyx_PyFunction_FastCall(func, args, nargs)\
    __Pyx_PyFunction_FastCallDict((func), (args), (nargs), NULL)
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, Py_ssize_t nargs, PyObject *kwargs);
#else
#define __Pyx_PyFunction_FastCallDict(func, args, nargs, kwargs) _PyFunction_FastCallDict(func, args, nargs, kwargs)
#endif
#define __Pyx_BUILD_ASSERT_EXPR(cond)\
    (sizeof(char [1 - 2*!(cond)]) - 1)
#ifndef Py_MEMBER_SIZE
#define Py_MEMBER_SIZE(type, member) sizeof(((type *)0)->member)
#endif
#if CYTHON_FAST_PYCALL
  static size_t __pyx_pyframe_localsplus_offset = 0;
  #include "frameobject.h"
#if PY_VERSION_HEX >= 0x030b00a6
  #ifndef Py_BUILD_CORE
    #define Py_BUILD_CORE 1
  #endif
  #include "internal/pycore_frame.h"
#endif
  #define __Pxy_PyFrame_Initialize_Offsets()\
    ((void)__Pyx_BUILD_ASSERT_EXPR(sizeof(PyFrameObject) == offsetof(PyFrameObject, f_localsplus) + Py_MEMBER_SIZE(PyFrameObject, f_localsplus)),\
     (void)(__pyx_pyframe_localsplus_offset = ((size_t)PyFrame_Type.tp_basicsize) - Py_MEMBER_SIZE(PyFrameObject, f_localsplus)))
  #define __Pyx_PyFrame_GetLocalsplus(frame)\
    (assert(__pyx_pyframe_localsplus_offset), (PyObject **)(((char *)(frame)) + __pyx_pyframe_localsplus_offset))
#endif // CYTHON_FAST_PYCALL
#endif

/* PyObjectCall.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* PyObjectCallMethO.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

/* PyDictVersioning.proto */
#if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_TYPE_SLOTS
#define __PYX_DICT_VERSION_INIT  ((PY_UINT64_T) -1)
#define __PYX_GET_DICT_VERSION(dict)  (((PyDictObject*)(dict))->ma_version_tag)
#define __PYX_UPDATE_DICT_CACHE(dict, value, cache_var, version_var)\
    (version_var) = __PYX_GET_DICT_VERSION(dict);\
    (cache_var) = (value);
#define __PYX_PY_DICT_LOOKUP_IF_MODIFIED(VAR, DICT, LOOKUP) {\
    static PY_UINT64_T __pyx_dict_version = 0;\
    static PyObject *__pyx_dict_cached_value = NULL;\
    if (likely(__PYX_GET_DICT_VERSION(DICT) == __pyx_dict_version)) {\
        (VAR) = __pyx_dict_cached_value;\
    } else {\
        (VAR) = __pyx_dict_cached_value = (LOOKUP);\
        __pyx_dict_version = __PYX_GET_DICT_VERSION(DICT);\
    }\
}
static CYTHON_INLINE PY_UINT64_T __Pyx_get_tp_dict_version(PyObject *obj);
static CYTHON_INLINE PY_UINT64_T __Pyx_get_object_dict_version(PyObject *obj);
static CYTHON_INLINE int __Pyx_object_dict_version_matches(PyObject* obj, PY_UINT64_T tp_dict_version, PY_UINT64_T obj_dict_version);
#else
#define __PYX_GET_DICT_VERSION(dict)  (0)
#define __PYX_UPDATE_DICT_CACHE(dict, value, cache_var, version_var)
#define __PYX_PY_DICT_LOOKUP_IF_MODIFIED(VAR, DICT, LOOKUP)  (VAR) = (LOOKUP);
#endif

/* GetModuleGlobalName.proto */
#if CYTHON_USE_DICT_VERSIONS
#define __Pyx_GetModuleGlobalName(var, name)  do {\
    static PY_UINT64_T __pyx_dict_version = 0;\
    static PyObject *__pyx_dict_cached_value = NULL;\
    (var) = (likely(__pyx_dict_version == __PYX_GET_DICT_VERSION(__pyx_d))) ?\
        (likely(__pyx_dict_cached_value) ? __Pyx_NewRef(__pyx_dict_cached_value) : __Pyx_GetBuiltinName(name)) :\
        __Pyx__GetModuleGlobalName(name, &__pyx_dict_version, &__pyx_dict_cached_value);\
} while(0)
#define __Pyx_GetModuleGlobalNameUncached(var, name)  do {\
    PY_UINT64_T __pyx_dict_version;\
    PyObject *__pyx_dict_cached_value;\
    (var) = __Pyx__GetModuleGlobalName(name, &__pyx_dict_version, &__pyx_dict_cached_value);\
} while(0)
static PyObject *__Pyx__GetModuleGlobalName(PyObject *name, PY_UINT64_T *dict_version, PyObject **dict_cached_value);
#else
#define __Pyx_GetModuleGlobalName(var, name)  (var) = __Pyx__GetModuleGlobalName(name)
#define __Pyx_GetModuleGlobalNameUncached(var, name)  (var) = __Pyx__GetModuleGlobalName(name)
static CYTHON_INLINE PyObject *__Pyx__GetModuleGlobalName(PyObject *name);
#endif

/* PyObjectCallNoArg.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* PyObjectCall2Args.proto */
static CYTHON_UNUSED PyObject* __Pyx_PyObject_Call2Args(PyObject* function, PyObject* arg1, PyObject* arg2);

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_SubtractObjC(PyObject *op1, PyObject *op2, long intval, int inplace, int zerodivision_check);
#else
#define __Pyx_PyInt_SubtractObjC(op1, op2, intval, inplace, zerodivision_check)\
    (inplace ? PyNumber_InPlaceSubtract(op1, op2) : PyNumber_Subtract(op1, op2))
#endif

/* GetItemInt.proto */
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) :\
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) :\
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

/* ObjectGetItem.proto */
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject *__Pyx_PyObject_GetItem(PyObject *obj, PyObject* key);
#else
#define __Pyx_PyObject_GetItem(obj, key)  PyObject_GetItem(obj, key)
#endif

/* ListAppend.proto */
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_PyList_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len) & likely(len > (L->allocated >> 1))) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        __Pyx_SET_SIZE(list, len + 1);
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_PyList_Append(L,x) PyList_Append(L,x)
#endif

/* PyObjectGetMethod.proto */
static int __Pyx_PyObject_GetMethod(PyObject *obj, PyObject *name, PyObject **method);

/* PyObjectCallMethod1.proto */
static PyObject* __Pyx_PyObject_CallMethod1(PyObject* obj, PyObject* method_name, PyObject* arg);

/* append.proto */
static CYTHON_INLINE int __Pyx_PyObject_Append(PyObject* L, PyObject* x);

/* None.proto */
static CYTHON_INLINE void __Pyx_RaiseClosureNameError(const char *varname);

/* ListCompAppend.proto */
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_ListComp_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len)) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        __Pyx_SET_SIZE(list, len + 1);
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_ListComp_Append(L,x) PyList_Append(L,x)
#endif

/* StringJoin.proto */
#if PY_MAJOR_VERSION < 3
#define __Pyx_PyString_Join __Pyx_PyBytes_Join
#define __Pyx_PyBaseString_Join(s, v) (PyUnicode_CheckExact(s) ? PyUnicode_Join(s, v) : __Pyx_PyBytes_Join(s, v))
#else
#define __Pyx_PyString_Join PyUnicode_Join
#define __Pyx_PyBaseString_Join PyUnicode_Join
#endif
#if CYTHON_COMPILING_IN_CPYTHON
    #if PY_MAJOR_VERSION < 3
    #define __Pyx_PyBytes_Join _PyString_Join
    #else
    #define __Pyx_PyBytes_Join _PyBytes_Join
    #endif
#else
static CYTHON_INLINE PyObject* __Pyx_PyBytes_Join(PyObject* sep, PyObject* values);
#endif

/* RaiseTooManyValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

/* RaiseNeedMoreValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

/* IterFinish.proto */
static CYTHON_INLINE int __Pyx_IterFinish(void);

/* UnpackItemEndCheck.proto */
static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected);

/* PySequenceContains.proto */
static CYTHON_INLINE int __Pyx_PySequence_ContainsTF(PyObject* item, PyObject* seq, int eq) {
    int result = PySequence_Contains(seq, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

/* IncludeStringH.proto */
#include <string.h>

/* JoinPyUnicode.proto */
static PyObject* __Pyx_PyUnicode_Join(PyObject* value_tuple, Py_ssize_t value_count, Py_ssize_t result_ulength,
                                      Py_UCS4 max_char);

/* BytesEquals.proto */
static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals);

/* UnicodeEquals.proto */
static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals);

/* StrEquals.proto */
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyString_Equals __Pyx_PyUnicode_Equals
#else
#define __Pyx_PyString_Equals __Pyx_PyBytes_Equals
#endif

/* SliceObject.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetSlice(
        PyObject* obj, Py_ssize_t cstart, Py_ssize_t cstop,
        PyObject** py_start, PyObject** py_stop, PyObject** py_slice,
        int has_cstart, int has_cstop, int wraparound);

/* GetTopmostException.proto */
#if CYTHON_USE_EXC_INFO_STACK
static _PyErr_StackItem * __Pyx_PyErr_GetTopmostException(PyThreadState *tstate);
#endif

/* PyThreadStateGet.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyThreadState_declare  PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign  __pyx_tstate = __Pyx_PyThreadState_Current;
#define __Pyx_PyErr_Occurred()  __pyx_tstate->curexc_type
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#define __Pyx_PyErr_Occurred()  PyErr_Occurred()
#endif

/* SaveResetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSave(type, value, tb)  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb)  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb)   PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb)  PyErr_SetExcInfo(type, value, tb)
#endif

/* GetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_GetException(type, value, tb)  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* PyErrExceptionMatches.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_ExceptionMatches(err) __Pyx_PyErr_ExceptionMatchesInState(__pyx_tstate, err)
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err);
#else
#define __Pyx_PyErr_ExceptionMatches(err)  PyErr_ExceptionMatches(err)
#endif

/* PyErrFetchRestore.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_Clear() __Pyx_ErrRestore(NULL, NULL, NULL)
#define __Pyx_ErrRestoreWithState(type, value, tb)  __Pyx_ErrRestoreInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)    __Pyx_ErrFetchInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  __Pyx_ErrRestoreInState(__pyx_tstate, type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)    __Pyx_ErrFetchInState(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyErr_SetNone(exc) (Py_INCREF(exc), __Pyx_ErrRestore((exc), NULL, NULL))
#else
#define __Pyx_PyErr_SetNone(exc) PyErr_SetNone(exc)
#endif
#else
#define __Pyx_PyErr_Clear() PyErr_Clear()
#define __Pyx_PyErr_SetNone(exc) PyErr_SetNone(exc)
#define __Pyx_ErrRestoreWithState(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestoreInState(tstate, type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchInState(tstate, type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)  PyErr_Fetch(type, value, tb)
#endif

/* DictGetItem.proto */
#if PY_MAJOR_VERSION >= 3 && !CYTHON_COMPILING_IN_PYPY
static PyObject *__Pyx_PyDict_GetItem(PyObject *d, PyObject* key);
#define __Pyx_PyObject_Dict_GetItem(obj, name)\
    (likely(PyDict_CheckExact(obj)) ?\
     __Pyx_PyDict_GetItem(obj, name) : PyObject_GetItem(obj, name))
#else
#define __Pyx_PyDict_GetItem(d, key) PyObject_GetItem(d, key)
#define __Pyx_PyObject_Dict_GetItem(obj, name)  PyObject_GetItem(obj, name)
#endif

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval, int inplace, int zerodivision_check);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace, zerodivision_check)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* FastTypeChecks.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_TypeCheck(obj, type) __Pyx_IsSubtype(Py_TYPE(obj), (PyTypeObject *)type)
static CYTHON_INLINE int __Pyx_IsSubtype(PyTypeObject *a, PyTypeObject *b);
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches(PyObject *err, PyObject *type);
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches2(PyObject *err, PyObject *type1, PyObject *type2);
#else
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#define __Pyx_PyErr_GivenExceptionMatches(err, type) PyErr_GivenExceptionMatches(err, type)
#define __Pyx_PyErr_GivenExceptionMatches2(err, type1, type2) (PyErr_GivenExceptionMatches(err, type1) || PyErr_GivenExceptionMatches(err, type2))
#endif
#define __Pyx_PyException_Check(obj) __Pyx_TypeCheck(obj, PyExc_Exception)

/* pyobject_as_double.proto */
static double __Pyx__PyObject_AsDouble(PyObject* obj);
#if CYTHON_COMPILING_IN_PYPY
#define __Pyx_PyObject_AsDouble(obj)\
(likely(PyFloat_CheckExact(obj)) ? PyFloat_AS_DOUBLE(obj) :\
 likely(PyInt_CheckExact(obj)) ?\
 PyFloat_AsDouble(obj) : __Pyx__PyObject_AsDouble(obj))
#else
#define __Pyx_PyObject_AsDouble(obj)\
((likely(PyFloat_CheckExact(obj))) ?\
 PyFloat_AS_DOUBLE(obj) : __Pyx__PyObject_AsDouble(obj))
#endif

/* FetchCommonType.proto */
static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type);

/* CythonFunctionShared.proto */
#define __Pyx_CyFunction_USED 1
#define __Pyx_CYFUNCTION_STATICMETHOD  0x01
#define __Pyx_CYFUNCTION_CLASSMETHOD   0x02
#define __Pyx_CYFUNCTION_CCLASS        0x04
#define __Pyx_CyFunction_GetClosure(f)\
    (((__pyx_CyFunctionObject *) (f))->func_closure)
#define __Pyx_CyFunction_GetClassObj(f)\
    (((__pyx_CyFunctionObject *) (f))->func_classobj)
#define __Pyx_CyFunction_Defaults(type, f)\
    ((type *)(((__pyx_CyFunctionObject *) (f))->defaults))
#define __Pyx_CyFunction_SetDefaultsGetter(f, g)\
    ((__pyx_CyFunctionObject *) (f))->defaults_getter = (g)
typedef struct {
    PyCFunctionObject func;
#if PY_VERSION_HEX < 0x030500A0
    PyObject *func_weakreflist;
#endif
    PyObject *func_dict;
    PyObject *func_name;
    PyObject *func_qualname;
    PyObject *func_doc;
    PyObject *func_globals;
    PyObject *func_code;
    PyObject *func_closure;
    PyObject *func_classobj;
    void *defaults;
    int defaults_pyobjects;
    size_t defaults_size;  // used by FusedFunction for copying defaults
    int flags;
    PyObject *defaults_tuple;
    PyObject *defaults_kwdict;
    PyObject *(*defaults_getter)(PyObject *);
    PyObject *func_annotations;
} __pyx_CyFunctionObject;
static PyTypeObject *__pyx_CyFunctionType = 0;
#define __Pyx_CyFunction_Check(obj)  (__Pyx_TypeCheck(obj, __pyx_CyFunctionType))
static PyObject *__Pyx_CyFunction_Init(__pyx_CyFunctionObject* op, PyMethodDef *ml,
                                      int flags, PyObject* qualname,
                                      PyObject *self,
                                      PyObject *module, PyObject *globals,
                                      PyObject* code);
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *m,
                                                         size_t size,
                                                         int pyobjects);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *m,
                                                            PyObject *tuple);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *m,
                                                             PyObject *dict);
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *m,
                                                              PyObject *dict);
static int __pyx_CyFunction_init(void);

/* CythonFunction.proto */
static PyObject *__Pyx_CyFunction_New(PyMethodDef *ml,
                                      int flags, PyObject* qualname,
                                      PyObject *closure,
                                      PyObject *module, PyObject *globals,
                                      PyObject* code);

/* PyIntCompare.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_EqObjC(PyObject *op1, PyObject *op2, long intval, long inplace);

/* py_abs.proto */
#if CYTHON_USE_PYLONG_INTERNALS
static PyObject *__Pyx_PyLong_AbsNeg(PyObject *num);
#define __Pyx_PyNumber_Absolute(x)\
    ((likely(PyLong_CheckExact(x))) ?\
         (likely(Py_SIZE(x) >= 0) ? (Py_INCREF(x), (x)) : __Pyx_PyLong_AbsNeg(x)) :\
         PyNumber_Absolute(x))
#else
#define __Pyx_PyNumber_Absolute(x)  PyNumber_Absolute(x)
#endif

/* GetAttr.proto */
static CYTHON_INLINE PyObject *__Pyx_GetAttr(PyObject *, PyObject *);

/* RaiseException.proto */
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause);

/* PyObjectLookupSpecial.proto */
#if CYTHON_USE_PYTYPE_LOOKUP && CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_LookupSpecial(PyObject* obj, PyObject* attr_name) {
    PyObject *res;
    PyTypeObject *tp = Py_TYPE(obj);
#if PY_MAJOR_VERSION < 3
    if (unlikely(PyInstance_Check(obj)))
        return __Pyx_PyObject_GetAttrStr(obj, attr_name);
#endif
    res = _PyType_Lookup(tp, attr_name);
    if (likely(res)) {
        descrgetfunc f = Py_TYPE(res)->tp_descr_get;
        if (!f) {
            Py_INCREF(res);
        } else {
            res = f(res, obj, (PyObject *)tp);
        }
    } else {
        PyErr_SetObject(PyExc_AttributeError, attr_name);
    }
    return res;
}
#else
#define __Pyx_PyObject_LookupSpecial(o,n) __Pyx_PyObject_GetAttrStr(o,n)
#endif

/* None.proto */
static CYTHON_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname);

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* PyObject_GenericGetAttrNoDict.proto */
#if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static CYTHON_INLINE PyObject* __Pyx_PyObject_GenericGetAttrNoDict(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GenericGetAttrNoDict PyObject_GenericGetAttr
#endif

/* ImportFrom.proto */
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

/* CalculateMetaclass.proto */
static PyObject *__Pyx_CalculateMetaclass(PyTypeObject *metaclass, PyObject *bases);

/* SetNameInClass.proto */
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030500A1
#define __Pyx_SetNameInClass(ns, name, value)\
    (likely(PyDict_CheckExact(ns)) ? _PyDict_SetItem_KnownHash(ns, name, value, ((PyASCIIObject *) name)->hash) : PyObject_SetItem(ns, name, value))
#elif CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_SetNameInClass(ns, name, value)\
    (likely(PyDict_CheckExact(ns)) ? PyDict_SetItem(ns, name, value) : PyObject_SetItem(ns, name, value))
#else
#define __Pyx_SetNameInClass(ns, name, value)  PyObject_SetItem(ns, name, value)
#endif

/* Py3ClassCreate.proto */
static PyObject *__Pyx_Py3MetaclassPrepare(PyObject *metaclass, PyObject *bases, PyObject *name, PyObject *qualname,
                                           PyObject *mkw, PyObject *modname, PyObject *doc);
static PyObject *__Pyx_Py3ClassCreate(PyObject *metaclass, PyObject *name, PyObject *bases, PyObject *dict,
                                      PyObject *mkw, int calculate_metaclass, int allow_py2_metaclass);

/* CLineInTraceback.proto */
#ifdef CYTHON_CLINE_IN_TRACEBACK
#define __Pyx_CLineForTraceback(tstate, c_line)  (((CYTHON_CLINE_IN_TRACEBACK)) ? c_line : 0)
#else
static int __Pyx_CLineForTraceback(PyThreadState *tstate, int c_line);
#endif

/* CodeObjectCache.proto */
typedef struct {
    PyCodeObject* code_object;
    int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

/* AddTraceback.proto */
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

/* GCCDiagnostics.proto */
#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define __Pyx_HAS_GCC_DIAGNOSTIC
#endif

/* Print.proto */
static int __Pyx_Print(PyObject*, PyObject *, int);
#if CYTHON_COMPILING_IN_PYPY || PY_MAJOR_VERSION >= 3
static PyObject* __pyx_print = 0;
static PyObject* __pyx_print_kwargs = 0;
#endif

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

/* PrintOne.proto */
static int __Pyx_PrintOne(PyObject* stream, PyObject *o);

/* Globals.proto */
static PyObject* __Pyx_Globals(void);

/* CIntFromPy.proto */
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

/* SwapException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSwap(type, value, tb)  __Pyx__ExceptionSwap(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSwap(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static CYTHON_INLINE void __Pyx_ExceptionSwap(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* CoroutineBase.proto */
typedef PyObject *(*__pyx_coroutine_body_t)(PyObject *, PyThreadState *, PyObject *);
#if CYTHON_USE_EXC_INFO_STACK
#define __Pyx_ExcInfoStruct  _PyErr_StackItem
#else
typedef struct {
    PyObject *exc_type;
    PyObject *exc_value;
    PyObject *exc_traceback;
} __Pyx_ExcInfoStruct;
#endif
typedef struct {
    PyObject_HEAD
    __pyx_coroutine_body_t body;
    PyObject *closure;
    __Pyx_ExcInfoStruct gi_exc_state;
    PyObject *gi_weakreflist;
    PyObject *classobj;
    PyObject *yieldfrom;
    PyObject *gi_name;
    PyObject *gi_qualname;
    PyObject *gi_modulename;
    PyObject *gi_code;
    PyObject *gi_frame;
    int resume_label;
    char is_running;
} __pyx_CoroutineObject;
static __pyx_CoroutineObject *__Pyx__Coroutine_New(
    PyTypeObject *type, __pyx_coroutine_body_t body, PyObject *code, PyObject *closure,
    PyObject *name, PyObject *qualname, PyObject *module_name);
static __pyx_CoroutineObject *__Pyx__Coroutine_NewInit(
            __pyx_CoroutineObject *gen, __pyx_coroutine_body_t body, PyObject *code, PyObject *closure,
            PyObject *name, PyObject *qualname, PyObject *module_name);
static CYTHON_INLINE void __Pyx_Coroutine_ExceptionClear(__Pyx_ExcInfoStruct *self);
static int __Pyx_Coroutine_clear(PyObject *self);
static PyObject *__Pyx_Coroutine_Send(PyObject *self, PyObject *value);
static PyObject *__Pyx_Coroutine_Close(PyObject *self);
static PyObject *__Pyx_Coroutine_Throw(PyObject *gen, PyObject *args);
#if CYTHON_USE_EXC_INFO_STACK
#define __Pyx_Coroutine_SwapException(self)
#define __Pyx_Coroutine_ResetAndClearException(self)  __Pyx_Coroutine_ExceptionClear(&(self)->gi_exc_state)
#else
#define __Pyx_Coroutine_SwapException(self) {\
    __Pyx_ExceptionSwap(&(self)->gi_exc_state.exc_type, &(self)->gi_exc_state.exc_value, &(self)->gi_exc_state.exc_traceback);\
    __Pyx_Coroutine_ResetFrameBackpointer(&(self)->gi_exc_state);\
    }
#define __Pyx_Coroutine_ResetAndClearException(self) {\
    __Pyx_ExceptionReset((self)->gi_exc_state.exc_type, (self)->gi_exc_state.exc_value, (self)->gi_exc_state.exc_traceback);\
    (self)->gi_exc_state.exc_type = (self)->gi_exc_state.exc_value = (self)->gi_exc_state.exc_traceback = NULL;\
    }
#endif
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyGen_FetchStopIterationValue(pvalue)\
    __Pyx_PyGen__FetchStopIterationValue(__pyx_tstate, pvalue)
#else
#define __Pyx_PyGen_FetchStopIterationValue(pvalue)\
    __Pyx_PyGen__FetchStopIterationValue(__Pyx_PyThreadState_Current, pvalue)
#endif
static int __Pyx_PyGen__FetchStopIterationValue(PyThreadState *tstate, PyObject **pvalue);
static CYTHON_INLINE void __Pyx_Coroutine_ResetFrameBackpointer(__Pyx_ExcInfoStruct *exc_state);

/* PatchModuleWithCoroutine.proto */
static PyObject* __Pyx_Coroutine_patch_module(PyObject* module, const char* py_code);

/* PatchGeneratorABC.proto */
static int __Pyx_patch_abc(void);

/* Generator.proto */
#define __Pyx_Generator_USED
static PyTypeObject *__pyx_GeneratorType = 0;
#define __Pyx_Generator_CheckExact(obj) (Py_TYPE(obj) == __pyx_GeneratorType)
#define __Pyx_Generator_New(body, code, closure, name, qualname, module_name)\
    __Pyx__Coroutine_New(__pyx_GeneratorType, body, code, closure, name, qualname, module_name)
static PyObject *__Pyx_Generator_Next(PyObject *self);
static int __pyx_Generator_init(void);

/* CheckBinaryVersion.proto */
static int __Pyx_check_binary_version(void);

/* InitStrings.proto */
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);


/* Module declarations from 'HP' */
static PyTypeObject *__pyx_ptype_2HP___pyx_scope_struct__sum = 0;
static PyTypeObject *__pyx_ptype_2HP___pyx_scope_struct_1_genexpr = 0;
static PyTypeObject *__pyx_ptype_2HP___pyx_scope_struct_2___str__ = 0;
static PyTypeObject *__pyx_ptype_2HP___pyx_scope_struct_3_genexpr = 0;
static PyTypeObject *__pyx_ptype_2HP___pyx_scope_struct_4___init__ = 0;
static PyTypeObject *__pyx_ptype_2HP___pyx_scope_struct_5__execute_for_loop = 0;
#define __Pyx_MODULE_NAME "HP"
extern int __pyx_module_is_main_HP;
int __pyx_module_is_main_HP = 0;

/* Implementation of 'HP' */
static PyObject *__pyx_builtin_staticmethod;
static PyObject *__pyx_builtin_input;
static PyObject *__pyx_builtin_sum;
static PyObject *__pyx_builtin_min;
static PyObject *__pyx_builtin_max;
static PyObject *__pyx_builtin_ValueError;
static PyObject *__pyx_builtin_enumerate;
static PyObject *__pyx_builtin_TypeError;
static PyObject *__pyx_builtin_eval;
static PyObject *__pyx_builtin_ZeroDivisionError;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_open;
static const char __pyx_k_[] = "%";
static const char __pyx_k_a[] = "a";
static const char __pyx_k_b[] = "\\b";
static const char __pyx_k_d[] = "d";
static const char __pyx_k_e[] = "e";
static const char __pyx_k_f[] = "}f";
static const char __pyx_k_i[] = "i";
static const char __pyx_k_k[] = "k";
static const char __pyx_k_l[] = "l";
static const char __pyx_k_m[] = "m";
static const char __pyx_k_n[] = "n";
static const char __pyx_k_p[] = "p";
static const char __pyx_k_r[] = "r";
static const char __pyx_k_s[] = "s";
static const char __pyx_k_v[] = "v";
static const char __pyx_k_w[] = "^(\\w+)\\((.*)\\)$";
static const char __pyx_k_0m[] = "\033[0m";
static const char __pyx_k_HP[] = "HP";
static const char __pyx_k__3[] = "[";
static const char __pyx_k__4[] = ", ";
static const char __pyx_k__5[] = "]";
static const char __pyx_k__6[] = "\"";
static const char __pyx_k__7[] = ":";
static const char __pyx_k__8[] = "; ";
static const char __pyx_k__9[] = "";
static const char __pyx_k_az[] = "az";
static const char __pyx_k_bv[] = "bv";
static const char __pyx_k_ch[] = "ch";
static const char __pyx_k_cm[] = "cm";
static const char __pyx_k_en[] = "en";
static const char __pyx_k_ev[] = "ev";
static const char __pyx_k_fn[] = "fn";
static const char __pyx_k_ft[] = "ft";
static const char __pyx_k_hp[] = ".hp";
static const char __pyx_k_ia[] = "ia";
static const char __pyx_k_in[] = "in";
static const char __pyx_k_lv[] = "lv";
static const char __pyx_k_nt[] = "nt";
static const char __pyx_k_op[] = "op";
static const char __pyx_k_os[] = "os";
static const char __pyx_k_pm[] = "pm";
static const char __pyx_k_re[] = "re";
static const char __pyx_k_rv[] = "rv";
static const char __pyx_k_ss[] = "ss";
static const char __pyx_k_st[] = "st";
static const char __pyx_k_ta[] = "ta";
static const char __pyx_k_tm[] = "tm";
static const char __pyx_k_to[] = "to";
static const char __pyx_k_vn[] = "vn";
static const char __pyx_k_vs[] = "vs";
static const char __pyx_k_91m[] = "\033[91m";
static const char __pyx_k_92m[] = "\033[92m";
static const char __pyx_k_93m[] = "\033[93m";
static const char __pyx_k_94m[] = "\033[94m";
static const char __pyx_k_95m[] = "\033[95m";
static const char __pyx_k_96m[] = "\033[96m";
static const char __pyx_k_97m[] = "\033[97m";
static const char __pyx_k_RUN[] = "RUN";
static const char __pyx_k__11[] = "\n";
static const char __pyx_k__12[] = "': ";
static const char __pyx_k__13[] = ".";
static const char __pyx_k__15[] = "'";
static const char __pyx_k__16[] = "(";
static const char __pyx_k__17[] = ")";
static const char __pyx_k__18[] = "$";
static const char __pyx_k__19[] = "!";
static const char __pyx_k__20[] = "!!";
static const char __pyx_k__21[] = "|";
static const char __pyx_k__23[] = "\\$";
static const char __pyx_k__24[] = "\\((.+)\\)$";
static const char __pyx_k__26[] = "^";
static const char __pyx_k__27[] = "<=";
static const char __pyx_k__28[] = ">=";
static const char __pyx_k__29[] = "!=";
static const char __pyx_k__30[] = "==";
static const char __pyx_k__31[] = "<";
static const char __pyx_k__32[] = ">";
static const char __pyx_k__34[] = " ";
static const char __pyx_k__35[] = "\" ";
static const char __pyx_k__36[] = " \"";
static const char __pyx_k__40[] = "*";
static const char __pyx_k__41[] = "/";
static const char __pyx_k__44[] = "+";
static const char __pyx_k__45[] = "-";
static const char __pyx_k__47[] = "\"'";
static const char __pyx_k__48[] = "([{";
static const char __pyx_k__49[] = ")]}";
static const char __pyx_k__50[] = ",";
static const char __pyx_k__52[] = ";";
static const char __pyx_k__53[] = "{";
static const char __pyx_k__54[] = "}";
static const char __pyx_k__59[] = "=";
static const char __pyx_k__61[] = "...";
static const char __pyx_k__65[] = "\n\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224";
static const char __pyx_k_abs[] = "abs";
static const char __pyx_k_add[] = "add";
static const char __pyx_k_avg[] = "avg";
static const char __pyx_k_b_2[] = "b";
static const char __pyx_k_cls[] = "cls";
static const char __pyx_k_cos[] = "cos";
static const char __pyx_k_cur[] = "cur";
static const char __pyx_k_dar[] = "dar";
static const char __pyx_k_day[] = "day";
static const char __pyx_k_doc[] = "__doc__";
static const char __pyx_k_end[] = "end";
static const char __pyx_k_f_2[] = "f";
static const char __pyx_k_for[] = "for";
static const char __pyx_k_ftp[] = "ftp";
static const char __pyx_k_gam[] = "gam";
static const char __pyx_k_gcd[] = "\\$gcd\\((.+),(.+)\\)$";
static const char __pyx_k_get[] = "get";
static const char __pyx_k_has[] = "has";
static const char __pyx_k_idx[] = "idx";
static const char __pyx_k_int[] = "int";
static const char __pyx_k_key[] = "key";
static const char __pyx_k_lcm[] = "\\$lcm\\((.+),(.+)\\)$";
static const char __pyx_k_log[] = "\\$log\\((.+)\\)$";
static const char __pyx_k_max[] = "max";
static const char __pyx_k_min[] = "min";
static const char __pyx_k_mod[] = "mod";
static const char __pyx_k_msg[] = "msg";
static const char __pyx_k_now[] = "now";
static const char __pyx_k_num[] = "num";
static const char __pyx_k_obj[] = "obj";
static const char __pyx_k_old[] = "old";
static const char __pyx_k_red[] = "red";
static const char __pyx_k_res[] = "res";
static const char __pyx_k_rnd[] = "rnd";
static const char __pyx_k_rng[] = "rng";
static const char __pyx_k_set[] = "set";
static const char __pyx_k_sin[] = "sin";
static const char __pyx_k_str[] = "str";
static const char __pyx_k_sub[] = "sub";
static const char __pyx_k_sum[] = "sum";
static const char __pyx_k_sys[] = "sys";
static const char __pyx_k_tan[] = "tan";
static const char __pyx_k_try[] = "try";
static const char __pyx_k_val[] = "val";
static const char __pyx_k_var[] = "var";
static const char __pyx_k_w_2[] = "\\((\\w+)\\)$";
static const char __pyx_k_w_d[] = "^(\\w+)\\[(\\d+)\\]$";
static const char __pyx_k_w_w[] = "^(\\w+)\\.(\\w+)\\((.*)\\)$";
static const char __pyx_k_agar[] = "agar";
static const char __pyx_k_args[] = "args";
static const char __pyx_k_argv[] = "argv";
static const char __pyx_k_arrn[] = "arrn";
static const char __pyx_k_attr[] = "attr";
static const char __pyx_k_blue[] = "blue";
static const char __pyx_k_body[] = "body";
static const char __pyx_k_bool[] = "bool";
static const char __pyx_k_call[] = "call";
static const char __pyx_k_chap[] = "chap";
static const char __pyx_k_cond[] = "cond";
static const char __pyx_k_cyan[] = "cyan";
static const char __pyx_k_data[] = "data";
static const char __pyx_k_date[] = "date";
static const char __pyx_k_days[] = "days";
static const char __pyx_k_else[] = "else";
static const char __pyx_k_eval[] = "eval";
static const char __pyx_k_exit[] = "__exit__";
static const char __pyx_k_expr[] = "expr";
static const char __pyx_k_file[] = "file '";
static const char __pyx_k_from[] = "from";
static const char __pyx_k_func[] = "func";
static const char __pyx_k_hich[] = "hich";
static const char __pyx_k_hp_2[] = "hp";
static const char __pyx_k_in_q[] = "in_q";
static const char __pyx_k_in_s[] = "in\\s+(.+)";
static const char __pyx_k_init[] = "__init__";
static const char __pyx_k_item[] = "item";
static const char __pyx_k_iter[] = "__iter__";
static const char __pyx_k_join[] = "join";
static const char __pyx_k_keys[] = "keys";
static const char __pyx_k_left[] = "left";
static const char __pyx_k_line[] = "line";
static const char __pyx_k_loop[] = "loop";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_math[] = "math";
static const char __pyx_k_name[] = "name";
static const char __pyx_k_null[] = "null";
static const char __pyx_k_nums[] = "nums";
static const char __pyx_k_open[] = "open";
static const char __pyx_k_pair[] = "pair";
static const char __pyx_k_read[] = "read";
static const char __pyx_k_repr[] = "__repr__";
static const char __pyx_k_root[] = "root\\((.+),(.+)\\)$";
static const char __pyx_k_self[] = "self";
static const char __pyx_k_send[] = "send";
static const char __pyx_k_sqrt[] = "sqrt";
static const char __pyx_k_step[] = "step";
static const char __pyx_k_tabe[] = "tabe";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_text[] = "text";
static const char __pyx_k_time[] = "time";
static const char __pyx_k_true[] = "true";
static const char __pyx_k_when[] = "when";
static const char __pyx_k_year[] = "year";
static const char __pyx_k_Error[] = "Error: ";
static const char __pyx_k_HP_py[] = "HP.py";
static const char __pyx_k_Y_m_d[] = "%Y/%m/%d";
static const char __pyx_k_apply[] = "apply";
static const char __pyx_k_begir[] = "begir";
static const char __pyx_k_break[] = "break";
static const char __pyx_k_clear[] = "clear";
static const char __pyx_k_close[] = "close";
static const char __pyx_k_color[] = "color";
static const char __pyx_k_count[] = "count";
static const char __pyx_k_depth[] = "depth";
static const char __pyx_k_edame[] = "edame";
static const char __pyx_k_enter[] = "__enter__";
static const char __pyx_k_error[] = "error";
static const char __pyx_k_false[] = "false";
static const char __pyx_k_flags[] = "flags";
static const char __pyx_k_float[] = "float";
static const char __pyx_k_fname[] = "fname";
static const char __pyx_k_for_2[] = "for ";
static const char __pyx_k_gcd_2[] = "gcd";
static const char __pyx_k_green[] = "green";
static const char __pyx_k_index[] = "index";
static const char __pyx_k_inner[] = "inner";
static const char __pyx_k_input[] = "input";
static const char __pyx_k_items[] = "items";
static const char __pyx_k_k_str[] = "k_str";
static const char __pyx_k_khata[] = "khata";
static const char __pyx_k_lines[] = "lines";
static const char __pyx_k_log10[] = "log10";
static const char __pyx_k_lower[] = "lower";
static const char __pyx_k_match[] = "match";
static const char __pyx_k_mod_2[] = " mod ";
static const char __pyx_k_month[] = "month";
static const char __pyx_k_other[] = "other";
static const char __pyx_k_pairs[] = "pairs";
static const char __pyx_k_param[] = "param";
static const char __pyx_k_parts[] = "parts";
static const char __pyx_k_print[] = "print";
static const char __pyx_k_range[] = "range";
static const char __pyx_k_reset[] = "reset";
static const char __pyx_k_right[] = "right";
static const char __pyx_k_set_2[] = "set ";
static const char __pyx_k_split[] = "split";
static const char __pyx_k_start[] = "start";
static const char __pyx_k_str_2[] = "__str__";
static const char __pyx_k_strip[] = "strip";
static const char __pyx_k_sub_2[] = "__sub__";
static const char __pyx_k_throw[] = "throw";
static const char __pyx_k_today[] = "@today";
static const char __pyx_k_try_2[] = "try ";
static const char __pyx_k_upper[] = "upper";
static const char __pyx_k_utf_8[] = "utf-8";
static const char __pyx_k_value[] = "value";
static const char __pyx_k_w_s_s[] = "(\\w+)\\s*=\\s*(.+)";
static const char __pyx_k_w_w_2[] = "^(\\w+)\\.(\\w+)$";
static const char __pyx_k_white[] = "white";
static const char __pyx_k_write[] = "write";
static const char __pyx_k_HP_RUN[] = "HP.RUN";
static const char __pyx_k_add_to[] = "add_to";
static const char __pyx_k_always[] = "always";
static const char __pyx_k_append[] = "append";
static const char __pyx_k_baraye[] = "baraye";
static const char __pyx_k_call_2[] = "call ";
static const char __pyx_k_colors[] = "colors";
static const char __pyx_k_define[] = "define";
static const char __pyx_k_dorost[] = "dorost";
static const char __pyx_k_else_2[] = "} else";
static const char __pyx_k_else_3[] = "else {";
static const char __pyx_k_failed[] = " failed";
static const char __pyx_k_file_2[] = "file";
static const char __pyx_k_ghalat[] = "ghalat";
static const char __pyx_k_hazfAz[] = "hazfAz";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_length[] = "length";
static const char __pyx_k_loop_2[] = "loop ";
static const char __pyx_k_module[] = "__module__";
static const char __pyx_k_name_2[] = "__name__";
static const char __pyx_k_number[] = "number";
static const char __pyx_k_params[] = "params";
static const char __pyx_k_prompt[] = "prompt";
static const char __pyx_k_purple[] = "purple";
static const char __pyx_k_random[] = "random";
static const char __pyx_k_remove[] = "remove";
static const char __pyx_k_result[] = "result";
static const char __pyx_k_return[] = "return";
static const char __pyx_k_rsplit[] = "rsplit";
static const char __pyx_k_rstrip[] = "rstrip";
static const char __pyx_k_search[] = "search";
static const char __pyx_k_shekan[] = "shekan";
static const char __pyx_k_sqrt_2[] = "sqrt\\((.+)\\)$";
static const char __pyx_k_system[] = "system";
static const char __pyx_k_to_num[] = "_to_num";
static const char __pyx_k_values[] = "values";
static const char __pyx_k_when_2[] = "when ";
static const char __pyx_k_yellow[] = "yellow";
static const char __pyx_k_Percent[] = "Percent";
static const char __pyx_k_bargard[] = "bargard";
static const char __pyx_k_content[] = "content";
static const char __pyx_k_emtehan[] = "emtehan";
static const char __pyx_k_ezafeBe[] = "ezafeBe";
static const char __pyx_k_genexpr[] = "genexpr";
static const char __pyx_k_hamishe[] = "hamishe";
static const char __pyx_k_prepare[] = "__prepare__";
static const char __pyx_k_radians[] = "radians";
static const char __pyx_k_replace[] = "replace";
static const char __pyx_k_today_2[] = "today";
static const char __pyx_k_try_end[] = "try_end";
static const char __pyx_k_vagarna[] = "vagarna";
static const char __pyx_k_write_2[] = "write ";
static const char __pyx_k_FileName[] = "FileName: ";
static const char __pyx_k_HP_error[] = "HP.error";
static const char __pyx_k_SoloDate[] = "SoloDate";
static const char __pyx_k_SoloDict[] = "SoloDict";
static const char __pyx_k_add_to_2[] = "add_to ";
static const char __pyx_k_args_str[] = "args_str";
static const char __pyx_k_body_end[] = "body_end";
static const char __pyx_k_builtins[] = "builtins";
static const char __pyx_k_code_str[] = "code_str";
static const char __pyx_k_continue[] = "continue";
static const char __pyx_k_datetime[] = "datetime";
static const char __pyx_k_defaults[] = "defaults";
static const char __pyx_k_else_idx[] = "else_idx";
static const char __pyx_k_encoding[] = "encoding";
static const char __pyx_k_endswith[] = "endswith";
static const char __pyx_k_executor[] = "executor";
static const char __pyx_k_filename[] = "filename";
static const char __pyx_k_function[] = "function";
static const char __pyx_k_keywords[] = "keywords";
static const char __pyx_k_obj_name[] = "obj_name";
static const char __pyx_k_qualname[] = "__qualname__";
static const char __pyx_k_return_2[] = "return ";
static const char __pyx_k_run_loop[] = "run_loop";
static const char __pyx_k_strftime[] = "strftime";
static const char __pyx_k_HP___init[] = "HP.__init__";
static const char __pyx_k_SoloArray[] = "SoloArray";
static const char __pyx_k_TypeError[] = "TypeError";
static const char __pyx_k_abs_error[] = "abs error";
static const char __pyx_k_block_end[] = "block_end";
static const char __pyx_k_close_idx[] = "close_idx";
static const char __pyx_k_container[] = "container";
static const char __pyx_k_else_line[] = "else_line";
static const char __pyx_k_enumerate[] = "enumerate";
static const char __pyx_k_factorial[] = "factorial";
static const char __pyx_k_functions[] = "functions";
static const char __pyx_k_is_jalali[] = "is_jalali";
static const char __pyx_k_is_number[] = "_is_number";
static const char __pyx_k_jdatetime[] = "jdatetime";
static const char __pyx_k_metaclass[] = "__metaclass__";
static const char __pyx_k_next_line[] = "next_line";
static const char __pyx_k_not_found[] = "' not found";
static const char __pyx_k_print_exc[] = "print_exc";
static const char __pyx_k_rng_range[] = "rng_range";
static const char __pyx_k_timedelta[] = "timedelta";
static const char __pyx_k_traceback[] = "traceback";
static const char __pyx_k_translate[] = "translate";
static const char __pyx_k_try_lines[] = "try_lines";
static const char __pyx_k_variables[] = "variables";
static const char __pyx_k_HP__to_num[] = "HP._to_num";
static const char __pyx_k_IGNORECASE[] = "IGNORECASE";
static const char __pyx_k_ValueError[] = "ValueError";
static const char __pyx_k_baghimande[] = "baghimande";
static const char __pyx_k_body_lines[] = "body_lines";
static const char __pyx_k_body_start[] = "body_start";
static const char __pyx_k_color_text[] = "color_text";
static const char __pyx_k_format_val[] = "_format_val";
static const char __pyx_k_function_2[] = "function ";
static const char __pyx_k_old_values[] = "old_values";
static const char __pyx_k_params_str[] = "params_str";
static const char __pyx_k_parse_args[] = "_parse_args";
static const char __pyx_k_parse_dict[] = "_parse_dict";
static const char __pyx_k_quote_char[] = "quote_char";
static const char __pyx_k_root_error[] = "root error";
static const char __pyx_k_skip_block[] = "_skip_block";
static const char __pyx_k_sqrt_error[] = "sqrt error";
static const char __pyx_k_startswith[] = "startswith";
static const char __pyx_k_today_greg[] = "today_greg";
static const char __pyx_k_when_start[] = "when_start";
static const char __pyx_k_d_4_d_2_d_2[] = "@(\\d{4})/(\\d{2})/(\\d{2})$";
static const char __pyx_k_execute_try[] = "_execute_try";
static const char __pyx_k_for_s_w_s_s[] = "for\\s+(\\w+)\\s*~\\s*(.+)";
static const char __pyx_k_input_s_s_s[] = "input\\s*\\(\\s*\"([^\"]*)\"\\s*\\)";
static const char __pyx_k_jalali_date[] = "jalali_date";
static const char __pyx_k_method_name[] = "method_name";
static const char __pyx_k_remove_from[] = "remove_from";
static const char __pyx_k_set_s_w_s_s[] = "set\\s+(\\w+)\\s*=\\s*(.+)";
static const char __pyx_k_togregorian[] = "togregorian";
static const char __pyx_k_HP_translate[] = "HP.translate";
static const char __pyx_k_SoloDate_day[] = "SoloDate.day";
static const char __pyx_k_SoloDict_add[] = "SoloDict.add";
static const char __pyx_k_SoloDict_has[] = "SoloDict.has";
static const char __pyx_k_SoloDict_key[] = "SoloDict.key";
static const char __pyx_k_add_to_s_w_s[] = "add_to\\s+(\\w+)\\s+(.+)";
static const char __pyx_k_execute_code[] = "execute_code";
static const char __pyx_k_execute_line[] = "_execute_line";
static const char __pyx_k_execute_loop[] = "_execute_loop";
static const char __pyx_k_execute_when[] = "_execute_when";
static const char __pyx_k_needs_number[] = " needs number";
static const char __pyx_k_return_value[] = "return_value";
static const char __pyx_k_set_variable[] = "set_variable";
static const char __pyx_k_staticmethod[] = "staticmethod";
static const char __pyx_k_today_jalali[] = "today_jalali";
static const char __pyx_k_HP__is_number[] = "HP._is_number";
static const char __pyx_k_HP_color_text[] = "HP.color_text";
static const char __pyx_k_Percent___str[] = "Percent.__str__";
static const char __pyx_k_Percent_apply[] = "Percent.apply";
static const char __pyx_k_SoloArray_add[] = "SoloArray.add";
static const char __pyx_k_SoloArray_avg[] = "SoloArray.avg";
static const char __pyx_k_SoloArray_get[] = "SoloArray.get";
static const char __pyx_k_SoloArray_max[] = "SoloArray.max";
static const char __pyx_k_SoloArray_min[] = "SoloArray.min";
static const char __pyx_k_SoloArray_set[] = "SoloArray.set";
static const char __pyx_k_SoloArray_sum[] = "SoloArray.sum";
static const char __pyx_k_SoloDate_year[] = "SoloDate.year";
static const char __pyx_k_SoloDict_keys[] = "SoloDict.keys";
static const char __pyx_k_d_4_d_2_d_2_2[] = "@@(\\d{4})/(\\d{2})/(\\d{2})$";
static const char __pyx_k_else_body_end[] = "else_body_end";
static const char __pyx_k_execute_block[] = "_execute_block";
static const char __pyx_k_from_s_s_to_s[] = "from\\s+(.+)\\s+to\\s+(.+)";
static const char __pyx_k_fromgregorian[] = "fromgregorian";
static const char __pyx_k_remove_from_2[] = "remove_from ";
static const char __pyx_k_smart_convert[] = "smart_convert";
static const char __pyx_k_HP__format_val[] = "HP._format_val";
static const char __pyx_k_HP__parse_args[] = "HP._parse_args";
static const char __pyx_k_HP__parse_dict[] = "HP._parse_dict";
static const char __pyx_k_HP__skip_block[] = "HP._skip_block";
static const char __pyx_k_Percent___init[] = "Percent.__init__";
static const char __pyx_k_Percent___repr[] = "Percent.__repr__";
static const char __pyx_k_SoloDate___str[] = "SoloDate.__str__";
static const char __pyx_k_SoloDate___sub[] = "SoloDate.__sub__";
static const char __pyx_k_SoloDate_month[] = "SoloDate.month";
static const char __pyx_k_SoloDate_today[] = "SoloDate.today";
static const char __pyx_k_SoloDict___str[] = "SoloDict.__str__";
static const char __pyx_k_SoloDict_value[] = "SoloDict.value";
static const char __pyx_k_default_values[] = "default_values";
static const char __pyx_k_else_block_end[] = "else_block_end";
static const char __pyx_k_error_occurred[] = "error_occurred";
static const char __pyx_k_gregorian_date[] = "gregorian_date";
static const char __pyx_k_FunctionHandler[] = "FunctionHandler";
static const char __pyx_k_HP__execute_try[] = "HP._execute_try";
static const char __pyx_k_HP_execute_code[] = "HP.execute_code";
static const char __pyx_k_HP_set_variable[] = "HP.set_variable";
static const char __pyx_k_ReturnException[] = "ReturnException";
static const char __pyx_k_SoloArray___str[] = "SoloArray.__str__";
static const char __pyx_k_SoloDate___init[] = "SoloDate.__init__";
static const char __pyx_k_SoloDict___init[] = "SoloDict.__init__";
static const char __pyx_k_SoloDict___repr[] = "SoloDict.__repr__";
static const char __pyx_k_SoloDict_length[] = "SoloDict.length";
static const char __pyx_k_SoloDict_remove[] = "SoloDict.remove";
static const char __pyx_k_SoloDict_values[] = "SoloDict.values";
static const char __pyx_k_else_body_start[] = "else_body_start";
static const char __pyx_k_split_semicolon[] = "_split_semicolon";
static const char __pyx_k_HP__execute_line[] = "HP._execute_line";
static const char __pyx_k_HP__execute_loop[] = "HP._execute_loop";
static const char __pyx_k_HP__execute_when[] = "HP._execute_when";
static const char __pyx_k_SoloArray___init[] = "SoloArray.__init__";
static const char __pyx_k_SoloArray___iter[] = "SoloArray.__iter__";
static const char __pyx_k_SoloArray___repr[] = "SoloArray.__repr__";
static const char __pyx_k_SoloArray_length[] = "SoloArray.length";
static const char __pyx_k_SoloArray_remove[] = "SoloArray.remove";
static const char __pyx_k_division_by_zero[] = "division by zero";
static const char __pyx_k_else_block_start[] = "else_block_start";
static const char __pyx_k_execute_for_loop[] = "_execute_for_loop";
static const char __pyx_k_function_handler[] = "function_handler";
static const char __pyx_k_invalid_for_loop[] = "invalid for loop";
static const char __pyx_k_to_jalali_string[] = "to_jalali_string";
static const char __pyx_k_Error_in_function[] = "Error in function '";
static const char __pyx_k_FileNotFoundError[] = "FileNotFoundError";
static const char __pyx_k_HP__execute_block[] = "HP._execute_block";
static const char __pyx_k_HP_v1_0_0_Running[] = "HP v1.0.0 - Running ";
static const char __pyx_k_Invalid_factorial[] = "Invalid factorial";
static const char __pyx_k_ZeroDivisionError[] = "ZeroDivisionError";
static const char __pyx_k_invalid_for_range[] = "invalid for range";
static const char __pyx_k_Execution_finished[] = "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\nExecution finished.";
static const char __pyx_k_call_object_method[] = "_call_object_method";
static const char __pyx_k_cline_in_traceback[] = "cline_in_traceback";
static const char __pyx_k_find_else_for_when[] = "find_else_for_when";
static const char __pyx_k_function_s_w_s_s_f[] = "function\\s+(\\w+)\\s*\\((.*)\\)\\s*f{";
static const char __pyx_k_log_needs_positive[] = "log needs positive";
static const char __pyx_k_undefined_variable[] = "undefined variable '";
static const char __pyx_k_HP__split_semicolon[] = "HP._split_semicolon";
static const char __pyx_k_evaluate_expression[] = "_evaluate_expression";
static const char __pyx_k_find_matching_brace[] = "find_matching_brace";
static const char __pyx_k_remove_from_s_w_s_d[] = "remove_from\\s+(\\w+)\\s+(\\d+)";
static const char __pyx_k_to_gregorian_string[] = "to_gregorian_string";
static const char __pyx_k_FunctionHandler_call[] = "FunctionHandler.call";
static const char __pyx_k_HP__execute_for_loop[] = "HP._execute_for_loop";
static const char __pyx_k_execute_function_def[] = "_execute_function_def";
static const char __pyx_k_invalid_function_def[] = "invalid function def";
static const char __pyx_k_HP_find_else_for_when[] = "HP.find_else_for_when";
static const char __pyx_k_evaluate_expression_2[] = "evaluate_expression";
static const char __pyx_k_FunctionHandler___init[] = "FunctionHandler.__init__";
static const char __pyx_k_FunctionHandler_define[] = "FunctionHandler.define";
static const char __pyx_k_HP__call_object_method[] = "HP._call_object_method";
static const char __pyx_k_HP_evaluate_expression[] = "HP.evaluate_expression";
static const char __pyx_k_HP_find_matching_brace[] = "HP.find_matching_brace";
static const char __pyx_k_ReturnException___init[] = "ReturnException.__init__";
static const char __pyx_k_evaluate_write_content[] = "_evaluate_write_content";
static const char __pyx_k_from_s_s_to_s_s_step_s[] = "from\\s+(.+)\\s+to\\s+(.+)\\s+step\\s+(.+)";
static const char __pyx_k_integer_modulo_by_zero[] = "integer modulo by zero";
static const char __pyx_k_HP__evaluate_expression[] = "HP._evaluate_expression";
static const char __pyx_k_HP__execute_function_def[] = "HP._execute_function_def";
static const char __pyx_k_HP___init___locals_lambda[] = "HP.__init__.<locals>.<lambda>";
static const char __pyx_k_SoloDate_to_jalali_string[] = "SoloDate.to_jalali_string";
static const char __pyx_k_HP__evaluate_write_content[] = "HP._evaluate_write_content";
static const char __pyx_k_find_matching_function_end[] = "find_matching_function_end";
static const char __pyx_k_Only_hp_files_are_supported[] = "Only .hp files are supported!";
static const char __pyx_k_SoloArray_sum_locals_genexpr[] = "SoloArray.sum.<locals>.genexpr";
static const char __pyx_k_SoloDate_to_gregorian_string[] = "SoloDate.to_gregorian_string";
static const char __pyx_k_HP_find_matching_function_end[] = "HP.find_matching_function_end";
static const char __pyx_k_HP__execute_for_loop_locals_run[] = "HP._execute_for_loop.<locals>.run_loop";
static const char __pyx_k_red_green_yellow_blue_purple_cy[] = "(red|green|yellow|blue|purple|cyan|white)\\((.+)\\)$";
static const char __pyx_k_Factorial_of_negative_is_undefin[] = "Factorial of negative is undefined";
static const char __pyx_k_SoloArray___str___locals_genexpr[] = "SoloArray.__str__.<locals>.genexpr";
static PyObject *__pyx_kp_s_;
static PyObject *__pyx_kp_u_;
static PyObject *__pyx_kp_s_0m;
static PyObject *__pyx_kp_s_91m;
static PyObject *__pyx_kp_s_92m;
static PyObject *__pyx_kp_s_93m;
static PyObject *__pyx_kp_s_94m;
static PyObject *__pyx_kp_s_95m;
static PyObject *__pyx_kp_s_96m;
static PyObject *__pyx_kp_s_97m;
static PyObject *__pyx_kp_u_Error;
static PyObject *__pyx_kp_u_Error_in_function;
static PyObject *__pyx_kp_u_Execution_finished;
static PyObject *__pyx_kp_s_Factorial_of_negative_is_undefin;
static PyObject *__pyx_kp_s_FileName;
static PyObject *__pyx_n_s_FileNotFoundError;
static PyObject *__pyx_n_s_FunctionHandler;
static PyObject *__pyx_n_s_FunctionHandler___init;
static PyObject *__pyx_n_s_FunctionHandler_call;
static PyObject *__pyx_n_s_FunctionHandler_define;
static PyObject *__pyx_n_s_HP;
static PyObject *__pyx_n_s_HP_RUN;
static PyObject *__pyx_n_s_HP___init;
static PyObject *__pyx_n_s_HP___init___locals_lambda;
static PyObject *__pyx_n_s_HP__call_object_method;
static PyObject *__pyx_n_s_HP__evaluate_expression;
static PyObject *__pyx_n_s_HP__evaluate_write_content;
static PyObject *__pyx_n_s_HP__execute_block;
static PyObject *__pyx_n_s_HP__execute_for_loop;
static PyObject *__pyx_n_s_HP__execute_for_loop_locals_run;
static PyObject *__pyx_n_s_HP__execute_function_def;
static PyObject *__pyx_n_s_HP__execute_line;
static PyObject *__pyx_n_s_HP__execute_loop;
static PyObject *__pyx_n_s_HP__execute_try;
static PyObject *__pyx_n_s_HP__execute_when;
static PyObject *__pyx_n_s_HP__format_val;
static PyObject *__pyx_n_s_HP__is_number;
static PyObject *__pyx_n_s_HP__parse_args;
static PyObject *__pyx_n_s_HP__parse_dict;
static PyObject *__pyx_n_s_HP__skip_block;
static PyObject *__pyx_n_s_HP__split_semicolon;
static PyObject *__pyx_n_s_HP__to_num;
static PyObject *__pyx_n_s_HP_color_text;
static PyObject *__pyx_n_s_HP_error;
static PyObject *__pyx_n_s_HP_evaluate_expression;
static PyObject *__pyx_n_s_HP_execute_code;
static PyObject *__pyx_n_s_HP_find_else_for_when;
static PyObject *__pyx_n_s_HP_find_matching_brace;
static PyObject *__pyx_n_s_HP_find_matching_function_end;
static PyObject *__pyx_kp_s_HP_py;
static PyObject *__pyx_n_s_HP_set_variable;
static PyObject *__pyx_n_s_HP_translate;
static PyObject *__pyx_kp_u_HP_v1_0_0_Running;
static PyObject *__pyx_n_s_IGNORECASE;
static PyObject *__pyx_kp_s_Invalid_factorial;
static PyObject *__pyx_kp_s_Only_hp_files_are_supported;
static PyObject *__pyx_n_s_Percent;
static PyObject *__pyx_n_s_Percent___init;
static PyObject *__pyx_n_s_Percent___repr;
static PyObject *__pyx_n_s_Percent___str;
static PyObject *__pyx_n_s_Percent_apply;
static PyObject *__pyx_n_s_RUN;
static PyObject *__pyx_n_s_ReturnException;
static PyObject *__pyx_n_s_ReturnException___init;
static PyObject *__pyx_n_s_SoloArray;
static PyObject *__pyx_n_s_SoloArray___init;
static PyObject *__pyx_n_s_SoloArray___iter;
static PyObject *__pyx_n_s_SoloArray___repr;
static PyObject *__pyx_n_s_SoloArray___str;
static PyObject *__pyx_n_s_SoloArray___str___locals_genexpr;
static PyObject *__pyx_n_s_SoloArray_add;
static PyObject *__pyx_n_s_SoloArray_avg;
static PyObject *__pyx_n_s_SoloArray_get;
static PyObject *__pyx_n_s_SoloArray_length;
static PyObject *__pyx_n_s_SoloArray_max;
static PyObject *__pyx_n_s_SoloArray_min;
static PyObject *__pyx_n_s_SoloArray_remove;
static PyObject *__pyx_n_s_SoloArray_set;
static PyObject *__pyx_n_s_SoloArray_sum;
static PyObject *__pyx_n_s_SoloArray_sum_locals_genexpr;
static PyObject *__pyx_n_s_SoloDate;
static PyObject *__pyx_n_s_SoloDate___init;
static PyObject *__pyx_n_s_SoloDate___str;
static PyObject *__pyx_n_s_SoloDate___sub;
static PyObject *__pyx_n_s_SoloDate_day;
static PyObject *__pyx_n_s_SoloDate_month;
static PyObject *__pyx_n_s_SoloDate_to_gregorian_string;
static PyObject *__pyx_n_s_SoloDate_to_jalali_string;
static PyObject *__pyx_n_s_SoloDate_today;
static PyObject *__pyx_n_s_SoloDate_year;
static PyObject *__pyx_n_s_SoloDict;
static PyObject *__pyx_n_s_SoloDict___init;
static PyObject *__pyx_n_s_SoloDict___repr;
static PyObject *__pyx_n_s_SoloDict___str;
static PyObject *__pyx_n_s_SoloDict_add;
static PyObject *__pyx_n_s_SoloDict_has;
static PyObject *__pyx_n_s_SoloDict_key;
static PyObject *__pyx_n_s_SoloDict_keys;
static PyObject *__pyx_n_s_SoloDict_length;
static PyObject *__pyx_n_s_SoloDict_remove;
static PyObject *__pyx_n_s_SoloDict_value;
static PyObject *__pyx_n_s_SoloDict_values;
static PyObject *__pyx_n_s_TypeError;
static PyObject *__pyx_n_s_ValueError;
static PyObject *__pyx_kp_s_Y_m_d;
static PyObject *__pyx_n_s_ZeroDivisionError;
static PyObject *__pyx_kp_s__11;
static PyObject *__pyx_kp_u__12;
static PyObject *__pyx_kp_s__13;
static PyObject *__pyx_kp_s__15;
static PyObject *__pyx_kp_u__15;
static PyObject *__pyx_kp_s__16;
static PyObject *__pyx_kp_s__17;
static PyObject *__pyx_kp_s__18;
static PyObject *__pyx_kp_s__19;
static PyObject *__pyx_kp_s__20;
static PyObject *__pyx_kp_s__21;
static PyObject *__pyx_kp_u__23;
static PyObject *__pyx_kp_u__24;
static PyObject *__pyx_kp_s__26;
static PyObject *__pyx_kp_u__26;
static PyObject *__pyx_kp_s__27;
static PyObject *__pyx_kp_s__28;
static PyObject *__pyx_kp_s__29;
static PyObject *__pyx_kp_s__3;
static PyObject *__pyx_kp_s__30;
static PyObject *__pyx_kp_s__31;
static PyObject *__pyx_kp_s__32;
static PyObject *__pyx_kp_u__34;
static PyObject *__pyx_kp_u__35;
static PyObject *__pyx_kp_u__36;
static PyObject *__pyx_kp_s__4;
static PyObject *__pyx_kp_s__40;
static PyObject *__pyx_kp_s__41;
static PyObject *__pyx_kp_s__44;
static PyObject *__pyx_kp_s__45;
static PyObject *__pyx_kp_s__47;
static PyObject *__pyx_kp_s__48;
static PyObject *__pyx_kp_s__49;
static PyObject *__pyx_kp_s__5;
static PyObject *__pyx_kp_s__50;
static PyObject *__pyx_kp_s__52;
static PyObject *__pyx_kp_s__53;
static PyObject *__pyx_kp_s__54;
static PyObject *__pyx_kp_s__59;
static PyObject *__pyx_kp_s__6;
static PyObject *__pyx_kp_u__6;
static PyObject *__pyx_kp_s__61;
static PyObject *__pyx_kp_u__65;
static PyObject *__pyx_kp_s__7;
static PyObject *__pyx_kp_u__7;
static PyObject *__pyx_kp_s__8;
static PyObject *__pyx_kp_s__9;
static PyObject *__pyx_n_s_a;
static PyObject *__pyx_n_s_abs;
static PyObject *__pyx_kp_s_abs_error;
static PyObject *__pyx_n_s_add;
static PyObject *__pyx_n_s_add_to;
static PyObject *__pyx_kp_s_add_to_2;
static PyObject *__pyx_kp_s_add_to_s_w_s;
static PyObject *__pyx_n_s_agar;
static PyObject *__pyx_n_s_always;
static PyObject *__pyx_n_s_append;
static PyObject *__pyx_n_s_apply;
static PyObject *__pyx_n_s_args;
static PyObject *__pyx_n_s_args_str;
static PyObject *__pyx_n_s_argv;
static PyObject *__pyx_n_s_arrn;
static PyObject *__pyx_n_s_attr;
static PyObject *__pyx_n_s_avg;
static PyObject *__pyx_n_s_az;
static PyObject *__pyx_kp_u_b;
static PyObject *__pyx_n_s_b_2;
static PyObject *__pyx_n_s_baghimande;
static PyObject *__pyx_n_s_baraye;
static PyObject *__pyx_n_s_bargard;
static PyObject *__pyx_n_s_begir;
static PyObject *__pyx_n_s_block_end;
static PyObject *__pyx_n_s_blue;
static PyObject *__pyx_n_s_body;
static PyObject *__pyx_n_s_body_end;
static PyObject *__pyx_n_s_body_lines;
static PyObject *__pyx_n_s_body_start;
static PyObject *__pyx_n_s_bool;
static PyObject *__pyx_n_s_break;
static PyObject *__pyx_n_s_builtins;
static PyObject *__pyx_n_s_bv;
static PyObject *__pyx_n_s_call;
static PyObject *__pyx_kp_u_call_2;
static PyObject *__pyx_n_s_call_object_method;
static PyObject *__pyx_n_s_ch;
static PyObject *__pyx_n_s_chap;
static PyObject *__pyx_n_s_clear;
static PyObject *__pyx_n_s_cline_in_traceback;
static PyObject *__pyx_n_s_close;
static PyObject *__pyx_n_s_close_idx;
static PyObject *__pyx_n_s_cls;
static PyObject *__pyx_n_s_cm;
static PyObject *__pyx_n_s_code_str;
static PyObject *__pyx_n_s_color;
static PyObject *__pyx_n_s_color_text;
static PyObject *__pyx_n_s_colors;
static PyObject *__pyx_n_s_cond;
static PyObject *__pyx_n_s_container;
static PyObject *__pyx_n_s_content;
static PyObject *__pyx_n_s_continue;
static PyObject *__pyx_n_s_cos;
static PyObject *__pyx_n_s_count;
static PyObject *__pyx_n_s_cur;
static PyObject *__pyx_n_s_cyan;
static PyObject *__pyx_n_s_d;
static PyObject *__pyx_kp_s_d_4_d_2_d_2;
static PyObject *__pyx_kp_s_d_4_d_2_d_2_2;
static PyObject *__pyx_n_s_dar;
static PyObject *__pyx_n_s_data;
static PyObject *__pyx_n_s_date;
static PyObject *__pyx_n_s_datetime;
static PyObject *__pyx_n_s_day;
static PyObject *__pyx_n_s_days;
static PyObject *__pyx_n_s_default_values;
static PyObject *__pyx_n_s_defaults;
static PyObject *__pyx_n_s_define;
static PyObject *__pyx_n_s_depth;
static PyObject *__pyx_kp_s_division_by_zero;
static PyObject *__pyx_n_s_doc;
static PyObject *__pyx_n_s_dorost;
static PyObject *__pyx_n_s_e;
static PyObject *__pyx_n_s_edame;
static PyObject *__pyx_n_s_else;
static PyObject *__pyx_kp_s_else_2;
static PyObject *__pyx_kp_s_else_3;
static PyObject *__pyx_n_s_else_block_end;
static PyObject *__pyx_n_s_else_block_start;
static PyObject *__pyx_n_s_else_body_end;
static PyObject *__pyx_n_s_else_body_start;
static PyObject *__pyx_n_s_else_idx;
static PyObject *__pyx_n_s_else_line;
static PyObject *__pyx_n_s_emtehan;
static PyObject *__pyx_n_s_en;
static PyObject *__pyx_n_s_encoding;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_endswith;
static PyObject *__pyx_n_s_enter;
static PyObject *__pyx_n_s_enumerate;
static PyObject *__pyx_n_s_error;
static PyObject *__pyx_n_s_error_occurred;
static PyObject *__pyx_n_s_ev;
static PyObject *__pyx_n_s_eval;
static PyObject *__pyx_n_s_evaluate_expression;
static PyObject *__pyx_n_s_evaluate_expression_2;
static PyObject *__pyx_n_s_evaluate_write_content;
static PyObject *__pyx_n_s_execute_block;
static PyObject *__pyx_n_s_execute_code;
static PyObject *__pyx_n_s_execute_for_loop;
static PyObject *__pyx_n_s_execute_function_def;
static PyObject *__pyx_n_s_execute_line;
static PyObject *__pyx_n_s_execute_loop;
static PyObject *__pyx_n_s_execute_try;
static PyObject *__pyx_n_s_execute_when;
static PyObject *__pyx_n_s_executor;
static PyObject *__pyx_n_s_exit;
static PyObject *__pyx_n_s_expr;
static PyObject *__pyx_n_s_ezafeBe;
static PyObject *__pyx_kp_s_f;
static PyObject *__pyx_n_s_f_2;
static PyObject *__pyx_n_s_factorial;
static PyObject *__pyx_kp_u_failed;
static PyObject *__pyx_n_s_false;
static PyObject *__pyx_kp_u_file;
static PyObject *__pyx_n_s_file_2;
static PyObject *__pyx_n_s_filename;
static PyObject *__pyx_n_s_find_else_for_when;
static PyObject *__pyx_n_s_find_matching_brace;
static PyObject *__pyx_n_s_find_matching_function_end;
static PyObject *__pyx_n_s_flags;
static PyObject *__pyx_n_s_float;
static PyObject *__pyx_n_s_fn;
static PyObject *__pyx_n_s_fname;
static PyObject *__pyx_n_s_for;
static PyObject *__pyx_kp_s_for_2;
static PyObject *__pyx_kp_s_for_s_w_s_s;
static PyObject *__pyx_n_s_format_val;
static PyObject *__pyx_n_s_from;
static PyObject *__pyx_kp_s_from_s_s_to_s;
static PyObject *__pyx_kp_s_from_s_s_to_s_s_step_s;
static PyObject *__pyx_n_s_fromgregorian;
static PyObject *__pyx_n_s_ft;
static PyObject *__pyx_n_s_ftp;
static PyObject *__pyx_n_s_func;
static PyObject *__pyx_n_s_function;
static PyObject *__pyx_kp_s_function_2;
static PyObject *__pyx_n_s_function_handler;
static PyObject *__pyx_kp_s_function_s_w_s_s_f;
static PyObject *__pyx_n_s_functions;
static PyObject *__pyx_n_s_gam;
static PyObject *__pyx_kp_s_gcd;
static PyObject *__pyx_n_s_gcd_2;
static PyObject *__pyx_n_s_genexpr;
static PyObject *__pyx_n_s_get;
static PyObject *__pyx_n_s_ghalat;
static PyObject *__pyx_n_s_green;
static PyObject *__pyx_n_s_gregorian_date;
static PyObject *__pyx_n_s_hamishe;
static PyObject *__pyx_n_s_has;
static PyObject *__pyx_n_s_hazfAz;
static PyObject *__pyx_n_s_hich;
static PyObject *__pyx_kp_s_hp;
static PyObject *__pyx_n_s_hp_2;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_n_s_ia;
static PyObject *__pyx_n_s_idx;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_in;
static PyObject *__pyx_n_s_in_q;
static PyObject *__pyx_kp_s_in_s;
static PyObject *__pyx_n_s_index;
static PyObject *__pyx_n_s_init;
static PyObject *__pyx_n_s_inner;
static PyObject *__pyx_n_s_input;
static PyObject *__pyx_kp_s_input_s_s_s;
static PyObject *__pyx_n_s_int;
static PyObject *__pyx_kp_s_integer_modulo_by_zero;
static PyObject *__pyx_kp_s_invalid_for_loop;
static PyObject *__pyx_kp_s_invalid_for_range;
static PyObject *__pyx_kp_s_invalid_function_def;
static PyObject *__pyx_n_s_is_jalali;
static PyObject *__pyx_n_s_is_number;
static PyObject *__pyx_n_s_item;
static PyObject *__pyx_n_s_items;
static PyObject *__pyx_n_s_iter;
static PyObject *__pyx_n_s_jalali_date;
static PyObject *__pyx_n_s_jdatetime;
static PyObject *__pyx_n_s_join;
static PyObject *__pyx_n_s_k;
static PyObject *__pyx_n_s_k_str;
static PyObject *__pyx_n_s_key;
static PyObject *__pyx_n_s_keys;
static PyObject *__pyx_n_s_keywords;
static PyObject *__pyx_n_s_khata;
static PyObject *__pyx_n_s_l;
static PyObject *__pyx_kp_s_lcm;
static PyObject *__pyx_n_s_left;
static PyObject *__pyx_n_s_length;
static PyObject *__pyx_n_s_line;
static PyObject *__pyx_n_s_lines;
static PyObject *__pyx_kp_s_log;
static PyObject *__pyx_n_s_log10;
static PyObject *__pyx_kp_s_log_needs_positive;
static PyObject *__pyx_n_s_loop;
static PyObject *__pyx_kp_s_loop_2;
static PyObject *__pyx_n_s_lower;
static PyObject *__pyx_n_s_lv;
static PyObject *__pyx_n_s_m;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_match;
static PyObject *__pyx_n_s_math;
static PyObject *__pyx_n_s_max;
static PyObject *__pyx_n_s_metaclass;
static PyObject *__pyx_n_s_method_name;
static PyObject *__pyx_n_s_min;
static PyObject *__pyx_n_s_mod;
static PyObject *__pyx_kp_s_mod_2;
static PyObject *__pyx_n_s_module;
static PyObject *__pyx_n_s_month;
static PyObject *__pyx_n_s_msg;
static PyObject *__pyx_n_s_n;
static PyObject *__pyx_n_s_name;
static PyObject *__pyx_n_s_name_2;
static PyObject *__pyx_kp_u_needs_number;
static PyObject *__pyx_n_s_next_line;
static PyObject *__pyx_kp_u_not_found;
static PyObject *__pyx_n_s_now;
static PyObject *__pyx_n_s_nt;
static PyObject *__pyx_n_s_null;
static PyObject *__pyx_n_s_num;
static PyObject *__pyx_n_s_number;
static PyObject *__pyx_n_s_nums;
static PyObject *__pyx_n_s_obj;
static PyObject *__pyx_n_s_obj_name;
static PyObject *__pyx_n_s_old;
static PyObject *__pyx_n_s_old_values;
static PyObject *__pyx_n_s_op;
static PyObject *__pyx_n_s_open;
static PyObject *__pyx_n_s_os;
static PyObject *__pyx_n_s_other;
static PyObject *__pyx_n_s_p;
static PyObject *__pyx_n_s_pair;
static PyObject *__pyx_n_s_pairs;
static PyObject *__pyx_n_s_param;
static PyObject *__pyx_n_s_params;
static PyObject *__pyx_n_s_params_str;
static PyObject *__pyx_n_s_parse_args;
static PyObject *__pyx_n_s_parse_dict;
static PyObject *__pyx_n_s_parts;
static PyObject *__pyx_n_s_pm;
static PyObject *__pyx_n_s_prepare;
static PyObject *__pyx_n_s_print;
static PyObject *__pyx_n_s_print_exc;
static PyObject *__pyx_n_s_prompt;
static PyObject *__pyx_n_s_purple;
static PyObject *__pyx_n_s_qualname;
static PyObject *__pyx_n_s_quote_char;
static PyObject *__pyx_n_s_r;
static PyObject *__pyx_n_s_radians;
static PyObject *__pyx_n_s_random;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_re;
static PyObject *__pyx_n_s_read;
static PyObject *__pyx_n_s_red;
static PyObject *__pyx_kp_s_red_green_yellow_blue_purple_cy;
static PyObject *__pyx_n_s_remove;
static PyObject *__pyx_n_s_remove_from;
static PyObject *__pyx_kp_s_remove_from_2;
static PyObject *__pyx_kp_s_remove_from_s_w_s_d;
static PyObject *__pyx_n_s_replace;
static PyObject *__pyx_n_s_repr;
static PyObject *__pyx_n_s_res;
static PyObject *__pyx_n_s_reset;
static PyObject *__pyx_n_s_result;
static PyObject *__pyx_n_s_return;
static PyObject *__pyx_kp_s_return_2;
static PyObject *__pyx_n_s_return_value;
static PyObject *__pyx_n_s_right;
static PyObject *__pyx_n_s_rnd;
static PyObject *__pyx_n_s_rng;
static PyObject *__pyx_n_s_rng_range;
static PyObject *__pyx_kp_s_root;
static PyObject *__pyx_kp_s_root_error;
static PyObject *__pyx_n_s_rsplit;
static PyObject *__pyx_n_s_rstrip;
static PyObject *__pyx_n_s_run_loop;
static PyObject *__pyx_n_s_rv;
static PyObject *__pyx_n_s_s;
static PyObject *__pyx_n_s_search;
static PyObject *__pyx_n_s_self;
static PyObject *__pyx_n_s_send;
static PyObject *__pyx_n_s_set;
static PyObject *__pyx_kp_s_set_2;
static PyObject *__pyx_kp_s_set_s_w_s_s;
static PyObject *__pyx_n_s_set_variable;
static PyObject *__pyx_n_s_shekan;
static PyObject *__pyx_n_s_sin;
static PyObject *__pyx_n_s_skip_block;
static PyObject *__pyx_n_s_smart_convert;
static PyObject *__pyx_n_s_split;
static PyObject *__pyx_n_s_split_semicolon;
static PyObject *__pyx_n_s_sqrt;
static PyObject *__pyx_kp_s_sqrt_2;
static PyObject *__pyx_kp_s_sqrt_error;
static PyObject *__pyx_n_s_ss;
static PyObject *__pyx_n_s_st;
static PyObject *__pyx_n_s_start;
static PyObject *__pyx_n_s_startswith;
static PyObject *__pyx_n_s_staticmethod;
static PyObject *__pyx_n_s_step;
static PyObject *__pyx_n_s_str;
static PyObject *__pyx_n_s_str_2;
static PyObject *__pyx_n_s_strftime;
static PyObject *__pyx_n_s_strip;
static PyObject *__pyx_n_s_sub;
static PyObject *__pyx_n_s_sub_2;
static PyObject *__pyx_n_s_sum;
static PyObject *__pyx_n_s_sys;
static PyObject *__pyx_n_s_system;
static PyObject *__pyx_n_s_ta;
static PyObject *__pyx_n_s_tabe;
static PyObject *__pyx_n_s_tan;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_text;
static PyObject *__pyx_n_s_throw;
static PyObject *__pyx_n_s_time;
static PyObject *__pyx_n_s_timedelta;
static PyObject *__pyx_n_s_tm;
static PyObject *__pyx_n_s_to;
static PyObject *__pyx_n_s_to_gregorian_string;
static PyObject *__pyx_n_s_to_jalali_string;
static PyObject *__pyx_n_s_to_num;
static PyObject *__pyx_kp_s_today;
static PyObject *__pyx_n_s_today_2;
static PyObject *__pyx_n_s_today_greg;
static PyObject *__pyx_n_s_today_jalali;
static PyObject *__pyx_n_s_togregorian;
static PyObject *__pyx_n_s_traceback;
static PyObject *__pyx_n_s_translate;
static PyObject *__pyx_n_s_true;
static PyObject *__pyx_n_s_try;
static PyObject *__pyx_kp_s_try_2;
static PyObject *__pyx_n_s_try_end;
static PyObject *__pyx_n_s_try_lines;
static PyObject *__pyx_kp_u_undefined_variable;
static PyObject *__pyx_n_s_upper;
static PyObject *__pyx_kp_s_utf_8;
static PyObject *__pyx_n_s_v;
static PyObject *__pyx_n_s_vagarna;
static PyObject *__pyx_n_s_val;
static PyObject *__pyx_n_s_value;
static PyObject *__pyx_n_s_values;
static PyObject *__pyx_n_s_var;
static PyObject *__pyx_n_s_variables;
static PyObject *__pyx_n_s_vn;
static PyObject *__pyx_n_s_vs;
static PyObject *__pyx_kp_s_w;
static PyObject *__pyx_kp_u_w_2;
static PyObject *__pyx_kp_s_w_d;
static PyObject *__pyx_kp_s_w_s_s;
static PyObject *__pyx_kp_s_w_w;
static PyObject *__pyx_kp_s_w_w_2;
static PyObject *__pyx_n_s_when;
static PyObject *__pyx_kp_s_when_2;
static PyObject *__pyx_n_s_when_start;
static PyObject *__pyx_n_s_white;
static PyObject *__pyx_n_s_write;
static PyObject *__pyx_kp_s_write_2;
static PyObject *__pyx_n_s_year;
static PyObject *__pyx_n_s_yellow;
static PyObject *__pyx_pf_2HP_15ReturnException___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_7Percent___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_7Percent_2apply(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_number); /* proto */
static PyObject *__pyx_pf_2HP_7Percent_4__str__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_7Percent_6__repr__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_year, PyObject *__pyx_v_month, PyObject *__pyx_v_day, PyObject *__pyx_v_is_jalali); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_2to_jalali_string(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_4to_gregorian_string(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_6__sub__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_other); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_8__str__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_10year(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_12month(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_14day(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDate_16today(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_items); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_2get(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_index); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_4set(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_6add(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_8remove(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_index); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_10length(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_3sum_genexpr(PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_12sum(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_14avg(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_16min(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_18max(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_7__str___genexpr(PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_20__str__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_22__repr__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_9SoloArray_24__iter__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_pairs); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_2value(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_key); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_4key(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_6add(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_key, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_8remove(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_key); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_10has(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_key); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_12keys(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_14values(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_16length(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_18__str__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_8SoloDict_20__repr__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_smart_convert(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_15FunctionHandler___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_15FunctionHandler_2define(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_name, PyObject *__pyx_v_params, PyObject *__pyx_v_body_lines, PyObject *__pyx_v_default_values); /* proto */
static PyObject *__pyx_pf_2HP_15FunctionHandler_4call(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_name, PyObject *__pyx_v_args, PyObject *__pyx_v_executor); /* proto */
static PyObject *__pyx_pf_2HP_2HP_translate(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_line); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda5(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda6(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda7(PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_pf_2HP_2HP_2__init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_2HP_2HP_4set_variable(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_name, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_2HP_2HP_6error(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_msg); /* proto */
static PyObject *__pyx_pf_2HP_2HP_8color_text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_text, PyObject *__pyx_v_color); /* proto */
static PyObject *__pyx_pf_2HP_2HP_10_is_number(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_v); /* proto */
static PyObject *__pyx_pf_2HP_2HP_12_to_num(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_v); /* proto */
static PyObject *__pyx_pf_2HP_2HP_14_format_val(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_val); /* proto */
static PyObject *__pyx_pf_2HP_2HP_16_evaluate_write_content(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_content); /* proto */
static PyObject *__pyx_pf_2HP_2HP_18_evaluate_expression(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_expr); /* proto */
static PyObject *__pyx_pf_2HP_2HP_20evaluate_expression(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_expr); /* proto */
static PyObject *__pyx_pf_2HP_2HP_22_call_object_method(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_obj, PyObject *__pyx_v_method_name, PyObject *__pyx_v_args); /* proto */
static PyObject *__pyx_pf_2HP_2HP_24_parse_args(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_s); /* proto */
static PyObject *__pyx_pf_2HP_2HP_26_parse_dict(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_content); /* proto */
static PyObject *__pyx_pf_2HP_2HP_28_split_semicolon(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_2HP_2HP_30find_matching_brace(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_lines, PyObject *__pyx_v_start); /* proto */
static PyObject *__pyx_pf_2HP_2HP_32find_else_for_when(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_lines, PyObject *__pyx_v_when_start); /* proto */
static PyObject *__pyx_pf_2HP_2HP_34find_matching_function_end(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_lines, PyObject *__pyx_v_start); /* proto */
static PyObject *__pyx_pf_2HP_2HP_36_execute_block(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_lines, PyObject *__pyx_v_start, PyObject *__pyx_v_end); /* proto */
static PyObject *__pyx_pf_2HP_2HP_38_execute_when(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__
