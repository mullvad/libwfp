#include "stdafx.h"
#include "conditionapplication.h"
#include "libwfp/internal/conditionassembler.h"
#include "libcommon/error.h"
#include <guiddef.h>
#include <fwpmu.h>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp {
namespace conditions {

ConditionApplication::ConditionApplication(const std::wstring &application)
	: m_application(application)
{
	FWP_BYTE_BLOB *blob;

	auto status = FwpmGetAppIdFromFileName(application.c_str(), &blob);

	THROW_UNLESS(ERROR_SUCCESS, status, L"Retrieve application identifier from filename")

	m_assembled = ConditionAssembler::ByteBlob(identifier(), FWP_MATCH_EQUAL, *blob);

	FwpmFreeMemory0((void**)&blob);
}

std::wstring ConditionApplication::toString() const
{
	return std::wstring(L"application = ").append(m_application);
}

const GUID &ConditionApplication::identifier() const
{
	return FWPM_CONDITION_ALE_APP_ID;
}

const FWPM_FILTER_CONDITION0 &ConditionApplication::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled->data);
}

}}
