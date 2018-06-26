

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 21 13:20:59 2018
 */
/* Compiler settings for SmartFilm.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_SmartFilmLib,0x83079A3C,0x1F35,0x465D,0x87,0x0E,0x22,0xF0,0x12,0x57,0xA5,0xB3);


MIDL_DEFINE_GUID(IID, DIID__DSmartFilm,0xF343D629,0x5863,0x4806,0xBA,0x82,0x04,0xDD,0x7D,0x83,0xDD,0x5D);


MIDL_DEFINE_GUID(IID, DIID__DSmartFilmEvents,0x0A2E3D85,0x99D0,0x44EF,0xA4,0x91,0xD5,0xA2,0x2C,0x31,0x23,0xDE);


MIDL_DEFINE_GUID(CLSID, CLSID_SmartFilm,0xB5E7A217,0xBC72,0x41D1,0x96,0x4B,0xF4,0x2D,0xBA,0x83,0x01,0xB5);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



