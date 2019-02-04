

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Jul 08 11:55:17 2008
 */
/* Compiler settings for .\pigeoncast.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __pigeoncastidl_h__
#define __pigeoncastidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___Dpigeoncast_FWD_DEFINED__
#define ___Dpigeoncast_FWD_DEFINED__
typedef interface _Dpigeoncast _Dpigeoncast;
#endif 	/* ___Dpigeoncast_FWD_DEFINED__ */


#ifndef ___DpigeoncastEvents_FWD_DEFINED__
#define ___DpigeoncastEvents_FWD_DEFINED__
typedef interface _DpigeoncastEvents _DpigeoncastEvents;
#endif 	/* ___DpigeoncastEvents_FWD_DEFINED__ */


#ifndef __pigeoncast_FWD_DEFINED__
#define __pigeoncast_FWD_DEFINED__

#ifdef __cplusplus
typedef class pigeoncast pigeoncast;
#else
typedef struct pigeoncast pigeoncast;
#endif /* __cplusplus */

#endif 	/* __pigeoncast_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __pigeoncastLib_LIBRARY_DEFINED__
#define __pigeoncastLib_LIBRARY_DEFINED__

/* library pigeoncastLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_pigeoncastLib;

#ifndef ___Dpigeoncast_DISPINTERFACE_DEFINED__
#define ___Dpigeoncast_DISPINTERFACE_DEFINED__

/* dispinterface _Dpigeoncast */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__Dpigeoncast;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D8BC263B-D805-4C36-A9D3-381E4129194F")
    _Dpigeoncast : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DpigeoncastVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _Dpigeoncast * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _Dpigeoncast * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _Dpigeoncast * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _Dpigeoncast * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _Dpigeoncast * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _Dpigeoncast * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _Dpigeoncast * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DpigeoncastVtbl;

    interface _Dpigeoncast
    {
        CONST_VTBL struct _DpigeoncastVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _Dpigeoncast_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _Dpigeoncast_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _Dpigeoncast_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _Dpigeoncast_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _Dpigeoncast_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _Dpigeoncast_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _Dpigeoncast_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___Dpigeoncast_DISPINTERFACE_DEFINED__ */


#ifndef ___DpigeoncastEvents_DISPINTERFACE_DEFINED__
#define ___DpigeoncastEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DpigeoncastEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DpigeoncastEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3A9ABC26-DD9A-42DD-8A8A-E8FF11B38458")
    _DpigeoncastEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DpigeoncastEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DpigeoncastEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DpigeoncastEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DpigeoncastEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DpigeoncastEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DpigeoncastEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DpigeoncastEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DpigeoncastEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DpigeoncastEventsVtbl;

    interface _DpigeoncastEvents
    {
        CONST_VTBL struct _DpigeoncastEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DpigeoncastEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DpigeoncastEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DpigeoncastEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DpigeoncastEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DpigeoncastEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DpigeoncastEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DpigeoncastEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DpigeoncastEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_pigeoncast;

#ifdef __cplusplus

class DECLSPEC_UUID("88C9CFCF-362D-4DE4-929C-2245C38B5BB4")
pigeoncast;
#endif
#endif /* __pigeoncastLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


