#pragma once

#include <Nexus/Patterns/FactoryObject.h>

#include <map>
#include <string>
#include <tinyxml2.h>
#include <iostream>

using tinyxml2::XMLError;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;
using tinyxml2::XMLDocument;

using std::map;
using std::string;

template<class T, class U>
concept derived = std::is_base_of_v<U, T>;

namespace Nexus
{
	class FactoryObject;

	class Factory
	{
	public:
		Factory(const char* _fileName);
		~Factory();

	public:
		template<derived<FactoryObject> OBJECT>
		void Build();

	protected:
		template<derived<FactoryObject> OBJECT>
		OBJECT* Get(const string& _name);

	private:
		XMLDocument* m_doc;
		char* m_fileName;

		map<string, FactoryObject*> m_factoryObjects;

	private:
		bool Initialise() const;

	};

	template <derived<FactoryObject> OBJECT>
	void Factory::Build()
	{
		if(!Initialise())
			return;

		// Iterate over all child nodes
		for(XMLNode* node = m_doc->FirstChildElement("Level")->FirstChildElement("Object"); node; node = node->NextSibling())
		{
			// Attempt to cast the node to an element type (this should always succeed)
			if(XMLElement* element = dynamic_cast<XMLElement*>(node))
			{
				// Attempt to get out the name of the object
				const char* name;
				const XMLError error = element->QueryStringAttribute("name", &name);
				if(error != XMLError::XML_SUCCESS)
					continue;

				// Convert the C style string to the std::string and check if it has already been recorded
				string strName = name;
				if(!m_factoryObjects.contains(strName))
				{
					// Record the object and parse it
					m_factoryObjects[strName] = new OBJECT;
					m_factoryObjects[strName]->Parse(element);
				}
				else
				{
					std::cerr << "Object with name: " << name << " has already been recorded!\n";
				}
			}
		}
	}

	template <derived<FactoryObject> OBJECT>
	OBJECT* Factory::Get(const string& _name)
	{
		if(m_factoryObjects.contains(_name))
			return static_cast<OBJECT*>(m_factoryObjects[_name]);

		return nullptr;
	}
}
