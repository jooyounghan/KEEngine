#pragma once
#include "XmlManager.h"
#include "ReflectObject.h"

namespace ke
{
	class ReflectXMLReadHandler : public XMLReader::XMLReadHandler
	{
	public:
		virtual ~ReflectXMLReadHandler() override = default;

	public:
		virtual void onReadElementStarted(const XMLReader::OnReadElementStartedArgs& args) override;
		virtual void onReadElementFinished(const XMLReader::OnReadElementEndArgs& args) override;
		virtual void onReadText(const XMLReader::OnReadTextArgs& args) override;
	};
}