#pragma once

// ReSharper disable CppInconsistentNaming
namespace tinyxml2
{
	class XMLElement;
}
// ReSharper restore CppInconsistentNaming

using tinyxml2::XMLElement;

namespace Nexus
{
	class FactoryObject
	{
	public:
		virtual ~FactoryObject();

	public:
		virtual void Parse(XMLElement* _element);

	};
}