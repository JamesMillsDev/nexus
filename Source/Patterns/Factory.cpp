#include <Nexus/Patterns/Factory.h>

namespace Nexus
{
	Factory::Factory(const char* _fileName)
		: m_doc{ new XMLDocument }, m_fileName{ new char[strlen(_fileName)] }
	{
		strcpy_s(m_fileName, strlen(_fileName) + 1, _fileName);
	}

	Factory::~Factory()
	{
		delete m_doc;
		m_doc = nullptr;

		delete[] m_fileName;
		m_fileName = nullptr;
	}

	bool Factory::Initialise() const
	{
		string path = "./assets/";
		path += m_fileName;
		path += ".xml";

		const XMLError error = m_doc->LoadFile(path.c_str());

		return error == XMLError::XML_SUCCESS;
	}
}
