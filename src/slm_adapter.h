#ifndef _SLM_ADAPTER_H_
#define _SLM_ADAPTER_H_

#include "slm_variant.h"

namespace SLManager
{
	class CAdapter
	{
		friend class CData;

	private:
		CData *m_pData;

		const string m_szKey;

		CAdapter(CData *pData, const string &szKey) : m_pData(pData), m_szKey(szKey) {}

	public:
		template <typename T> operator T() const { return m_pData->Get(m_szKey); }
		template <typename T> CVariant operator= (const T &Value) { return m_pData->Add(m_szKey, Value); }
	};
}

#endif // _SLM_ADAPTER_H_