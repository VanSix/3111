//////////////////////////////////////////////////////////////////////
// Video Capture using DirectShow
// Author: Shiqi Yu (shiqi.yu@gmail.com)
// Thanks to:
//		HardyAI@OpenCV China
//		flymanbox@OpenCV China (for his contribution to function CameraName, and frame width/height setting)
// Last modification: April 9, 2009
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// ʹ��˵����
//   1. ��CameraDS.h CameraDS.cpp�Լ�Ŀ¼DirectShow���Ƶ������Ŀ��
//   2. �˵� Project->Settings->Settings for:(All configurations)->C/C++->Category(Preprocessor)->Additional include directories
//      ����Ϊ DirectShow/Include
//   3. �˵� Project->Settings->Settings for:(All configurations)->Link->Category(Input)->Additional library directories
//      ����Ϊ DirectShow/Lib
//////////////////////////////////////////////////////////////////////

// CameraDS.cpp: implementation of the CCameraDS class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CameraDS.h"
#include <afxmt.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraDS::CCameraDS()
{
	m_bConnected = m_bLock = m_bChanged = false;
	m_nWidth = m_nHeight = 0;
	m_nBufferSize = 0;

	//m_pFrame = NULL;
	m_pImageData = NULL;


	m_pNullFilter = NULL;
	m_pMediaEvent = NULL;
	m_pSampleGrabberFilter = NULL;
	m_pGraph = NULL;
	m_pMediaEventEx = NULL;	

	CoInitialize(NULL);
}

CCameraDS::~CCameraDS()
{
	CloseCamera();
	CoUninitialize();

	TRACE("~CCameraDS\n");
}

void CCameraDS::CloseCamera()
{
	if(m_bConnected)
	{
		m_pMediaControl->Stop();
	}

	// 1.0Af
	// return code fail
	/*
	m_pGraph = NULL;
	m_pDeviceFilter = NULL;
	m_pMediaControl = NULL;
	m_pSampleGrabberFilter = NULL;
	m_pSampleGrabber = NULL;
	m_pGrabberInput = NULL;
	m_pGrabberOutput = NULL;
	m_pCameraOutput = NULL;
	m_pMediaEvent = NULL;
	m_pNullFilter = NULL;
	m_pNullInputPin = NULL;
	*/

	// 1.0Af
	// Detach, avoid return code fail
	m_pGraph.Detach();
	m_pDeviceFilter.Detach();
	m_pMediaControl.Detach();
	m_pSampleGrabberFilter.Detach();
	m_pSampleGrabber.Detach();
	m_pGrabberInput.Detach();
	m_pGrabberOutput.Detach();
	m_pCameraOutput.Detach();
	m_pMediaEvent.Detach();
	m_pNullFilter.Detach();
	m_pNullInputPin.Detach();

	if (m_pImageData)
	{
		delete [] m_pImageData;
		m_pImageData = NULL;
	}

	//
	if(m_pMediaEventEx != NULL)
	{
		m_pMediaEventEx->Release();
		m_pMediaEventEx = NULL;
	}

	m_bConnected = m_bLock = m_bChanged = false;
	m_nWidth = m_nHeight = 0;
	m_nBufferSize = 0;
}
// 1.0Af
// Remove this and re-build new one, avoid when program start no device cause the program crash.
/*
bool CCameraDS::OpenCamera(int nCamID, bool bDisplayProperties, int nWidth, int nHeight)
{
	HRESULT hr = S_OK;

	CoInitialize(NULL);
	// Create the Filter Graph Manager.
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&m_pGraph);
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (LPVOID *)&m_pSampleGrabberFilter);
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);
	hr = m_pGraph->QueryInterface(IID_IMediaEvent, (void **) &m_pMediaEvent);
	//
	hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *) &m_pMediaEventEx);
	//
	hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (LPVOID*) &m_pNullFilter);
	hr = m_pGraph->AddFilter(m_pNullFilter, L"NullRenderer");
	hr = m_pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&m_pSampleGrabber);

	AM_MEDIA_TYPE   mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	mt.formattype = FORMAT_VideoInfo; 
	hr = m_pSampleGrabber->SetMediaType(&mt);
	MYFREEMEDIATYPE(mt);

	m_pGraph->AddFilter(m_pSampleGrabberFilter, L"Grabber");
 
	// Bind Device Filter.  We know the device because the id was passed in
	BindFilter(nCamID, &m_pDeviceFilter);
	m_pGraph->AddFilter(m_pDeviceFilter, NULL);

	CComPtr<IEnumPins> pEnum;
	m_pDeviceFilter->EnumPins(&pEnum);
 
	hr = pEnum->Reset();
	hr = pEnum->Next(1, &m_pCameraOutput, NULL); 

	pEnum = NULL; 
	m_pSampleGrabberFilter->EnumPins(&pEnum);
	pEnum->Reset();
	hr = pEnum->Next(1, &m_pGrabberInput, NULL); 

	pEnum = NULL;
	m_pSampleGrabberFilter->EnumPins(&pEnum);
	pEnum->Reset();
	pEnum->Skip(1);
	hr = pEnum->Next(1, &m_pGrabberOutput, NULL); 

	pEnum = NULL;
	m_pNullFilter->EnumPins(&pEnum);
	pEnum->Reset();
	hr = pEnum->Next(1, &m_pNullInputPin, NULL);

	//SetCrossBar();

	if (bDisplayProperties) 
	{
		CComPtr<ISpecifyPropertyPages> pPages;

		HRESULT hr = m_pCameraOutput->QueryInterface(IID_ISpecifyPropertyPages, (void**)&pPages);
		if (SUCCEEDED(hr))
		{
			PIN_INFO PinInfo;
			m_pCameraOutput->QueryPinInfo(&PinInfo);

			CAUUID caGUID;
			pPages->GetPages(&caGUID);

			OleCreatePropertyFrame(NULL, 0, 0,
						L"Property Sheet", 1,
						(IUnknown **)&(m_pCameraOutput.p),
						caGUID.cElems, caGUID.pElems,
						0, 0, NULL);

			CoTaskMemFree(caGUID.pElems);
			PinInfo.pFilter->Release();
		}
		pPages = NULL;
	}
	else 
	{

		//////////////////////////////////////////////////////////////////////////////
		IAMStreamConfig *iconfig = NULL;
		hr = m_pCameraOutput->QueryInterface(IID_IAMStreamConfig, (void**)&iconfig);   

		AM_MEDIA_TYPE *pmt;
		if(iconfig->GetFormat(&pmt) !=S_OK)
		{
			//printf("GetFormat Failed ! \n");
			return false;
		}

		// 3
		if (((int)pmt->lSampleSize != (nWidth * nHeight * 3)) && (pmt->formattype == FORMAT_VideoInfo))
		{
			VIDEOINFOHEADER *phead = (VIDEOINFOHEADER*)(pmt->pbFormat);
			phead->bmiHeader.biWidth = nWidth;
			phead->bmiHeader.biHeight = nHeight;
			if((hr = iconfig->SetFormat(pmt)) != S_OK)
			{
				return false;
			}
		}

		iconfig->Release();
		iconfig=NULL;
		MYFREEMEDIATYPE(*pmt);
	}

	hr = m_pGraph->Connect(m_pCameraOutput, m_pGrabberInput);
	hr = m_pGraph->Connect(m_pGrabberOutput, m_pNullInputPin);

	if (FAILED(hr))
	{
		switch(hr)
		{
			case VFW_S_NOPREVIEWPIN :
				break;
			case E_FAIL :
				break;
			case E_INVALIDARG :
				break;
			case E_POINTER :
				break;
		}
	}

	m_pSampleGrabber->SetBufferSamples(TRUE);
	m_pSampleGrabber->SetOneShot(TRUE);
    
	hr = m_pSampleGrabber->GetConnectedMediaType(&mt);
	if(FAILED(hr))
	{
		return false;
	}

	VIDEOINFOHEADER *videoHeader;
	videoHeader = reinterpret_cast<VIDEOINFOHEADER*>(mt.pbFormat);
	m_nWidth = videoHeader->bmiHeader.biWidth;
	m_nHeight = videoHeader->bmiHeader.biHeight;
	m_bConnected = true;

	pEnum = NULL;
	return true;
}
*/
bool CCameraDS::OpenCamera(int nCamID, bool bDisplayProperties, int nWidth, int nHeight)
{
	HRESULT hr = S_OK;

	CoInitialize(NULL);
	// Create the Filter Graph Manager.
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&m_pGraph);
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (LPVOID *)&m_pSampleGrabberFilter);
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);
	hr = m_pGraph->QueryInterface(IID_IMediaEvent, (void **) &m_pMediaEvent);
	hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *) &m_pMediaEventEx);
	hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (LPVOID*) &m_pNullFilter);
	hr = m_pGraph->AddFilter(m_pNullFilter, L"NullRenderer");
	hr = m_pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&m_pSampleGrabber);

	AM_MEDIA_TYPE   mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	mt.formattype = FORMAT_VideoInfo; 
	hr = m_pSampleGrabber->SetMediaType(&mt);
	MYFREEMEDIATYPE(mt);

	m_pGraph->AddFilter(m_pSampleGrabberFilter, L"Grabber");
 
	// Bind Device Filter.  We know the device because the id was passed in
	bool bBinFilterResult = BindFilter(nCamID, &m_pDeviceFilter);
	HRESULT hrFilter = S_OK;
	hrFilter = m_pGraph->AddFilter(m_pDeviceFilter, NULL);
	if( hrFilter == S_OK )
		TRACE("Camera ID: %d\n AddFilter Success(No Error)\n", nCamID );
	else
	{
		TRACE("Camera ID: %d\n AddFilter Fail(Error)", nCamID );
		return false;
	}

	CComPtr<IEnumPins> pEnum;
	m_pDeviceFilter->EnumPins(&pEnum);
 
	hr = pEnum->Reset();
	hr = pEnum->Next(1, &m_pCameraOutput, NULL); 

	pEnum = NULL; 
	m_pSampleGrabberFilter->EnumPins(&pEnum);
	pEnum->Reset();
	hr = pEnum->Next(1, &m_pGrabberInput, NULL); 

	pEnum = NULL;
	m_pSampleGrabberFilter->EnumPins(&pEnum);
	pEnum->Reset();
	pEnum->Skip(1);
	hr = pEnum->Next(1, &m_pGrabberOutput, NULL); 

	pEnum = NULL;
	m_pNullFilter->EnumPins(&pEnum);
	pEnum->Reset();
	hr = pEnum->Next(1, &m_pNullInputPin, NULL);

	if (bDisplayProperties) 
	{
		CComPtr<ISpecifyPropertyPages> pPages;

		HRESULT hr = m_pCameraOutput->QueryInterface(IID_ISpecifyPropertyPages, (void**)&pPages);
		if (SUCCEEDED(hr))
		{
			PIN_INFO PinInfo;
			m_pCameraOutput->QueryPinInfo(&PinInfo);

			CAUUID caGUID;
			pPages->GetPages(&caGUID);

			OleCreatePropertyFrame(NULL, 0, 0,
						L"Property Sheet", 1,
						(IUnknown **)&(m_pCameraOutput.p),
						caGUID.cElems, caGUID.pElems,
						0, 0, NULL);

			CoTaskMemFree(caGUID.pElems);
			PinInfo.pFilter->Release();
		}
		pPages = NULL;
	}
	else 
	{

		//////////////////////////////////////////////////////////////////////////////
		IAMStreamConfig *iconfig = NULL;
		hr = m_pCameraOutput->QueryInterface(IID_IAMStreamConfig, (void**)&iconfig);   

		AM_MEDIA_TYPE *pmt;
		if(iconfig->GetFormat(&pmt) !=S_OK)
		{
			//printf("GetFormat Failed ! \n");
			return false;
		}

		// 3
		if (((int)pmt->lSampleSize != (nWidth * nHeight * 3)) && (pmt->formattype == FORMAT_VideoInfo))
		{
			VIDEOINFOHEADER *phead = (VIDEOINFOHEADER*)(pmt->pbFormat);
			phead->bmiHeader.biWidth = nWidth;
			phead->bmiHeader.biHeight = nHeight;
			if((hr = iconfig->SetFormat(pmt)) != S_OK)
			{
				return false;
			}
		}

		iconfig->Release();
		iconfig=NULL;
		MYFREEMEDIATYPE(*pmt);
	}

	hr = m_pGraph->Connect(m_pCameraOutput, m_pGrabberInput);
	hr = m_pGraph->Connect(m_pGrabberOutput, m_pNullInputPin);

	if (FAILED(hr))
	{
		switch(hr)
		{
			case VFW_S_NOPREVIEWPIN :
				break;
			case E_FAIL :
				break;
			case E_INVALIDARG :
				break;
			case E_POINTER :
				break;
		}
	}

	m_pSampleGrabber->SetBufferSamples(TRUE);
	m_pSampleGrabber->SetOneShot(TRUE);
    
	hr = m_pSampleGrabber->GetConnectedMediaType(&mt);
	if(FAILED(hr))
	{
		return false;
	}

	VIDEOINFOHEADER *videoHeader;
	videoHeader = reinterpret_cast<VIDEOINFOHEADER*>(mt.pbFormat);
	m_nWidth = videoHeader->bmiHeader.biWidth;
	m_nHeight = videoHeader->bmiHeader.biHeight;
	m_bConnected = true;

	pEnum = NULL;
	return true;
}


bool CCameraDS::BindFilter(int nCamID, IBaseFilter **pFilter)
{
	if (nCamID < 0)
	{
		return false;
	}
 
    // enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if (hr != NOERROR)
	{
		return false;
	}

    CComPtr<IEnumMoniker> pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if (hr != NOERROR) 
	{
		return false;
    }

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;
	int index = 0;
    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK, index <= nCamID)
    {
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				if (index == nCamID)
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);
				}
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
		index++;
    }

	pCreateDevEnum = NULL;
	return true;
}

//������crossbar���PhysConn_Video_Composite
void CCameraDS::SetCrossBar()
{
	int i;
	IAMCrossbar *pXBar1 = NULL;
	ICaptureGraphBuilder2 *pBuilder = NULL;
 
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void **)&pBuilder);

	if (SUCCEEDED(hr))
	{
		hr = pBuilder->SetFiltergraph(m_pGraph);
	}

	hr = pBuilder->FindInterface(&LOOK_UPSTREAM_ONLY, NULL, m_pDeviceFilter,IID_IAMCrossbar, (void**)&pXBar1);

	if (SUCCEEDED(hr)) 
	{
  		long OutputPinCount, InputPinCount;
		long PinIndexRelated, PhysicalType;
		long inPort = 0, outPort = 0;

		pXBar1->get_PinCounts(&OutputPinCount, &InputPinCount);
		for( i =0;i<InputPinCount;i++)
		{
			pXBar1->get_CrossbarPinInfo(TRUE,i,&PinIndexRelated,&PhysicalType);
			if(PhysConn_Video_Composite==PhysicalType) 
			{
				inPort = i;
				break;
			}
		}
		for( i =0;i<OutputPinCount;i++)
		{
			pXBar1->get_CrossbarPinInfo(FALSE,i,&PinIndexRelated,&PhysicalType);
			if(PhysConn_Video_VideoDecoder==PhysicalType) 
			{
				outPort = i;
				break;
			}
		}
  
		if(S_OK==pXBar1->CanRoute(outPort,inPort))
		{
			pXBar1->Route(outPort,inPort);
		}
		pXBar1->Release();  
	}
	pBuilder->Release();
}

/*
The returned image can not be released.
*/

void CCameraDS::SetMediaControl(bool bRun)
{
	long evCode;
	if(bRun)
	{
		m_pMediaControl->Run();
		m_pMediaEvent->WaitForCompletion(INFINITE, &evCode);		
	}
	else
		m_pMediaControl->Stop();
}

char* CCameraDS::QueryFrame(bool &cameraOK)
{
	//
	long evCode, size = 0;

	// Check Camera Status...
	LONG_PTR param1,param2;
	if(SUCCEEDED(m_pMediaEventEx->GetEvent(&evCode,&param1,&param2,100)))
	{
		m_pMediaEventEx->FreeEventParams(evCode,param1,param2);
		switch(evCode)
		{
		case EC_COMPLETE:
			break;
		case EC_USERABORT:
			break;
		case EC_ERRORABORT:
			break;
		case EC_DEVICE_LOST:
			cameraOK = true;
			break;
		}
	}
	// Check Camera Status Complete OK

	DWORD dStartTime = ::GetTickCount();
	m_pMediaControl->Run();
	m_pMediaEvent->WaitForCompletion(INFINITE, &evCode);			

	m_pSampleGrabber->GetCurrentBuffer(&size, NULL);
//	TRACE1("Capture Time %d \n",::GetTickCount()-dStartTime);

	//if the buffer size changed
	if (size != m_nBufferSize)
	{
		if (m_pImageData)
		{
			free(m_pImageData);
			m_pImageData =NULL;
		}

		m_nBufferSize = size;
		m_pImageData = new char[m_nBufferSize];
	}

	m_pSampleGrabber->GetCurrentBuffer(&m_nBufferSize, (long*)m_pImageData);
	ImageFlip(m_pImageData);

	return m_pImageData;
}

void CCameraDS::ImageFlip(char *pImageBuffer)
{
	int i;
	int iByteRow	= 640 * 3;
	int iCol = 480-1;
	int iChangCount	= 480/2;

	char *cTemp;
	char *cBuffer=new char[iByteRow];

	for(i=0;i<iChangCount;i++)
	{
		cTemp = pImageBuffer;
		memcpy(cBuffer,cTemp+((iCol-i)*iByteRow),iByteRow);
		memcpy(pImageBuffer+((iCol-i)*iByteRow),pImageBuffer+(i*iByteRow),iByteRow);
		memcpy(pImageBuffer+(i*iByteRow),cBuffer,iByteRow);
	}

	delete(cBuffer);
}
int CCameraDS::CameraCount()
{
	int count = 0;
 	CoInitialize(NULL);

   // enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);

    CComPtr<IEnumMoniker> pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if (hr != NOERROR) 
	{
		return count;
    }

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;
    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {
		count++;
    }

	pCreateDevEnum = NULL;
	pEm = NULL;
	return count;
}

int CCameraDS::CameraName(int nCamID, char* sName, int nBufferSize)
{
	int count = 0;
 	CoInitialize(NULL);

   // enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);

    CComPtr<IEnumMoniker> pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if (hr != NOERROR) return 0;

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;
    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {
		if (count == nCamID)
		{
			IPropertyBag *pBag=0;
			hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if(SUCCEEDED(hr))
			{
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName", &var, NULL); //������������,��������Ϣ�ȵ�...
	            if(hr == NOERROR)
		        {
			        //��ȡ�豸����			
					WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,sName, nBufferSize ,"",NULL);

	                SysFreeString(var.bstrVal);				
		        }
			    pBag->Release();
			}
			pM->Release();

			break;
		}
		count++;
    }

	pCreateDevEnum = NULL;
	pEm = NULL;

	return 1;
}

// ImageSize CCameraDS::setImageSize(int iwidth,int iheight)
// {
// 	ImageSize Size;
// 	Size.height=iheight;
// 	Size.width=iwidth;
// 	return Size;
// }

