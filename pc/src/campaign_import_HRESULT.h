// campaign_import_HRESULT.h -- the COM result type and its tests, as winerror.h declares them.

#ifndef CAMPAIGN_IMPORT_HRESULT_H
#define CAMPAIGN_IMPORT_HRESULT_H

typedef long HRESULT;

#define S_OK ((HRESULT)0L)
#define SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define FAILED(hr) ((HRESULT)(hr) < 0)

#endif
