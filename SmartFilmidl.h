

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Jun 06 13:10:06 2018
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SmartFilmidl_h__
#define __SmartFilmidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSmartFilm_FWD_DEFINED__
#define ___DSmartFilm_FWD_DEFINED__
typedef interface _DSmartFilm _DSmartFilm;
#endif 	/* ___DSmartFilm_FWD_DEFINED__ */


#ifndef ___DSmartFilmEvents_FWD_DEFINED__
#define ___DSmartFilmEvents_FWD_DEFINED__
typedef interface _DSmartFilmEvents _DSmartFilmEvents;
#endif 	/* ___DSmartFilmEvents_FWD_DEFINED__ */


#ifndef __SmartFilm_FWD_DEFINED__
#define __SmartFilm_FWD_DEFINED__

#ifdef __cplusplus
typedef class SmartFilm SmartFilm;
#else
typedef struct SmartFilm SmartFilm;
#endif /* __cplusplus */

#endif 	/* __SmartFilm_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SmartFilmLib_LIBRARY_DEFINED__
#define __SmartFilmLib_LIBRARY_DEFINED__

/* library SmartFilmLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_SmartFilmLib;

#ifndef ___DSmartFilm_DISPINTERFACE_DEFINED__
#define ___DSmartFilm_DISPINTERFACE_DEFINED__

/* dispinterface _DSmartFilm */
/* [uuid] */ 


EXTERN_C const IID DIID__DSmartFilm;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F343D629-5863-4806-BA82-04DD7D83DD5D")
    _DSmartFilm : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSmartFilmVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSmartFilm * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSmartFilm * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSmartFilm * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSmartFilm * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSmartFilm * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSmartFilm * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSmartFilm * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSmartFilmVtbl;

    interface _DSmartFilm
    {
        CONST_VTBL struct _DSmartFilmVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSmartFilm_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSmartFilm_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSmartFilm_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSmartFilm_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSmartFilm_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSmartFilm_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSmartFilm_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSmartFilm_DISPINTERFACE_DEFINED__ */


#ifndef ___DSmartFilmEvents_DISPINTERFACE_DEFINED__
#define ___DSmartFilmEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSmartFilmEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DSmartFilmEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0A2E3D85-99D0-44EF-A491-D5A22C3123DE")
    _DSmartFilmEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSmartFilmEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSmartFilmEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSmartFilmEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSmartFilmEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSmartFilmEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSmartFilmEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSmartFilmEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSmartFilmEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSmartFilmEventsVtbl;

    interface _DSmartFilmEvents
    {
        CONST_VTBL struct _DSmartFilmEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSmartFilmEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSmartFilmEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSmartFilmEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSmartFilmEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSmartFilmEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSmartFilmEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSmartFilmEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSmartFilmEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SmartFilm;

#ifdef __cplusplus

class DECLSPEC_UUID("B5E7A217-BC72-41D1-964B-F42DBA8301B5")
SmartFilm;
#endif
#endif /* __SmartFilmLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


