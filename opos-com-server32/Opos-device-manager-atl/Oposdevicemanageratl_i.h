

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 05:14:07 2038
 */
/* Compiler settings for Oposdevicemanageratl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Oposdevicemanageratl_i_h__
#define __Oposdevicemanageratl_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IOposDeviceManager_FWD_DEFINED__
#define __IOposDeviceManager_FWD_DEFINED__
typedef interface IOposDeviceManager IOposDeviceManager;

#endif 	/* __IOposDeviceManager_FWD_DEFINED__ */


#ifndef __IMyDeviceManagerEvents_FWD_DEFINED__
#define __IMyDeviceManagerEvents_FWD_DEFINED__
typedef interface IMyDeviceManagerEvents IMyDeviceManagerEvents;

#endif 	/* __IMyDeviceManagerEvents_FWD_DEFINED__ */


#ifndef ___IOposDeviceManagerEvents_FWD_DEFINED__
#define ___IOposDeviceManagerEvents_FWD_DEFINED__
typedef interface _IOposDeviceManagerEvents _IOposDeviceManagerEvents;

#endif 	/* ___IOposDeviceManagerEvents_FWD_DEFINED__ */


#ifndef __OposDeviceManager_FWD_DEFINED__
#define __OposDeviceManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class OposDeviceManager OposDeviceManager;
#else
typedef struct OposDeviceManager OposDeviceManager;
#endif /* __cplusplus */

#endif 	/* __OposDeviceManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IOposDeviceManager_INTERFACE_DEFINED__
#define __IOposDeviceManager_INTERFACE_DEFINED__

/* interface IOposDeviceManager */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IOposDeviceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2f1ee96f-1a60-4954-9ddd-c475b974253c")
    IOposDeviceManager : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartScanner( 
            /* [in] */ BSTR commandId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopScanner( 
            /* [in] */ BSTR commandId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableDataEvent( 
            /* [in] */ BSTR deviceId,
            /* [in] */ BSTR commandId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisableDataEvent( 
            /* [in] */ BSTR deviceId,
            /* [in] */ BSTR commandId) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOposDeviceManagerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOposDeviceManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOposDeviceManager * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOposDeviceManager * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IOposDeviceManager * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IOposDeviceManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IOposDeviceManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IOposDeviceManager * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IOposDeviceManager, StartScanner)
        HRESULT ( STDMETHODCALLTYPE *StartScanner )( 
            IOposDeviceManager * This,
            /* [in] */ BSTR commandId);
        
        DECLSPEC_XFGVIRT(IOposDeviceManager, StopScanner)
        HRESULT ( STDMETHODCALLTYPE *StopScanner )( 
            IOposDeviceManager * This,
            /* [in] */ BSTR commandId);
        
        DECLSPEC_XFGVIRT(IOposDeviceManager, EnableDataEvent)
        HRESULT ( STDMETHODCALLTYPE *EnableDataEvent )( 
            IOposDeviceManager * This,
            /* [in] */ BSTR deviceId,
            /* [in] */ BSTR commandId);
        
        DECLSPEC_XFGVIRT(IOposDeviceManager, DisableDataEvent)
        HRESULT ( STDMETHODCALLTYPE *DisableDataEvent )( 
            IOposDeviceManager * This,
            /* [in] */ BSTR deviceId,
            /* [in] */ BSTR commandId);
        
        END_INTERFACE
    } IOposDeviceManagerVtbl;

    interface IOposDeviceManager
    {
        CONST_VTBL struct IOposDeviceManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOposDeviceManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOposDeviceManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOposDeviceManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOposDeviceManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IOposDeviceManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IOposDeviceManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IOposDeviceManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IOposDeviceManager_StartScanner(This,commandId)	\
    ( (This)->lpVtbl -> StartScanner(This,commandId) ) 

#define IOposDeviceManager_StopScanner(This,commandId)	\
    ( (This)->lpVtbl -> StopScanner(This,commandId) ) 

#define IOposDeviceManager_EnableDataEvent(This,deviceId,commandId)	\
    ( (This)->lpVtbl -> EnableDataEvent(This,deviceId,commandId) ) 

#define IOposDeviceManager_DisableDataEvent(This,deviceId,commandId)	\
    ( (This)->lpVtbl -> DisableDataEvent(This,deviceId,commandId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOposDeviceManager_INTERFACE_DEFINED__ */


#ifndef __IMyDeviceManagerEvents_INTERFACE_DEFINED__
#define __IMyDeviceManagerEvents_INTERFACE_DEFINED__

/* interface IMyDeviceManagerEvents */
/* [object][version][hidden][dual][oleautomation][nonextensible][uuid] */ 


EXTERN_C const IID IID_IMyDeviceManagerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD22695F-84FF-427B-B763-B1DD8376E37E")
    IMyDeviceManagerEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnDataEvent( 
            /* [in] */ BSTR data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnCommandCompleted( 
            /* [in] */ BSTR commandId) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMyDeviceManagerEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyDeviceManagerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyDeviceManagerEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyDeviceManagerEvents * This);
        
        DECLSPEC_XFGVIRT(IMyDeviceManagerEvents, OnDataEvent)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnDataEvent )( 
            IMyDeviceManagerEvents * This,
            /* [in] */ BSTR data);
        
        DECLSPEC_XFGVIRT(IMyDeviceManagerEvents, OnCommandCompleted)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnCommandCompleted )( 
            IMyDeviceManagerEvents * This,
            /* [in] */ BSTR commandId);
        
        END_INTERFACE
    } IMyDeviceManagerEventsVtbl;

    interface IMyDeviceManagerEvents
    {
        CONST_VTBL struct IMyDeviceManagerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyDeviceManagerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyDeviceManagerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyDeviceManagerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyDeviceManagerEvents_OnDataEvent(This,data)	\
    ( (This)->lpVtbl -> OnDataEvent(This,data) ) 

#define IMyDeviceManagerEvents_OnCommandCompleted(This,commandId)	\
    ( (This)->lpVtbl -> OnCommandCompleted(This,commandId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyDeviceManagerEvents_INTERFACE_DEFINED__ */



#ifndef __OposdevicemanageratlLib_LIBRARY_DEFINED__
#define __OposdevicemanageratlLib_LIBRARY_DEFINED__

/* library OposdevicemanageratlLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_OposdevicemanageratlLib;

#ifndef ___IOposDeviceManagerEvents_DISPINTERFACE_DEFINED__
#define ___IOposDeviceManagerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IOposDeviceManagerEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IOposDeviceManagerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("47704e5b-bea7-4c8b-ada7-347e9515bdad")
    _IOposDeviceManagerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IOposDeviceManagerEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IOposDeviceManagerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IOposDeviceManagerEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IOposDeviceManagerEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IOposDeviceManagerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IOposDeviceManagerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IOposDeviceManagerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IOposDeviceManagerEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IOposDeviceManagerEventsVtbl;

    interface _IOposDeviceManagerEvents
    {
        CONST_VTBL struct _IOposDeviceManagerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IOposDeviceManagerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IOposDeviceManagerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IOposDeviceManagerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IOposDeviceManagerEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IOposDeviceManagerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IOposDeviceManagerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IOposDeviceManagerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IOposDeviceManagerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_OposDeviceManager;

#ifdef __cplusplus

class DECLSPEC_UUID("3c4ad21c-1f81-46e5-9d7f-3573f8b6302f")
OposDeviceManager;
#endif
#endif /* __OposdevicemanageratlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


