//
// Created by nhy20 on 2020-08-23.
//

#include <catch.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <memory>

tinyxml2::XMLDeclaration * add_declaration( tinyxml2::XMLDocument * p_doc )
{
	tinyxml2::XMLDeclaration * p_declaration = p_doc->NewDeclaration("tuna_xml");
	p_doc->LinkEndChild( p_declaration );
	return p_declaration;
}

void test_declaration( tinyxml2::XMLDocument * p_doc, tinyxml2::XMLDeclaration * p_declaration )
{
	REQUIRE( p_declaration != nullptr );
	REQUIRE( !p_doc->Error() );
	REQUIRE( p_doc->FirstChild()->ToDeclaration() );
}

tinyxml2::XMLElement * add_element( tinyxml2::XMLDocument * p_doc )
{
	tinyxml2::XMLElement *p_root_element = p_doc->NewElement("test_root_node");
	p_doc->LinkEndChild( p_root_element );
	return p_root_element;
}

SCENARIO("what is xml?", "[tinyxml]")
{
	GIVEN("a single xml document")
	{
		auto * p_doc = new tinyxml2::XMLDocument();

		WHEN("a single declaration")
		{
			tinyxml2::XMLDeclaration * p_declaration = add_declaration( p_doc );

			THEN("declaration not nullptr, no error.")
			{
				test_declaration( p_doc, p_declaration );
			}
		}

		WHEN("add root node")
		{
			add_element( p_doc );

			THEN("expect value.")
			{
				REQUIRE( strcmp( p_doc->FirstChild()->Value(), "test_root_node" ) == 0 );
			}
		}

		WHEN("a single xml document")
		{
			tinyxml2::XMLDeclaration * p_declaration = add_declaration( p_doc );
			add_element( p_doc );

			THEN("expect")
			{
				test_declaration( p_doc, p_declaration );
				REQUIRE( strcmp( p_doc->LastChild()->Value(), "test_root_node" ) == 0 );
			}
		}

		delete p_doc;
	}
}