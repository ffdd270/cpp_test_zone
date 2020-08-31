//
// Created by nhy20 on 2020-08-23.
//

#include <catch.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <cstring>

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

void add_element_property( tinyxml2::XMLElement * p_parent_element, const char * name_attr, bool open_attr )
{
	p_parent_element->SetAttribute("name", name_attr);
	p_parent_element->SetAttribute( "is_open", open_attr );
}

SCENARIO("what is xml?", "[tinyxml]")
{
	GIVEN("a single xml empty document")
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


	GIVEN("a single string")
	{
		std::string name = "Window_Test";

		WHEN("replace _ to space")
		{
			std::replace( name.begin(), name.end(), '_', ' ' );

			THEN(" no _. only space. ")
			{
				REQUIRE( name == "Window Test");
			}
		}


	}

	GIVEN("a single xml document")
	{
		auto * p_doc = new tinyxml2::XMLDocument();

		add_declaration( p_doc );
		add_element( p_doc );


		tinyxml2::XMLElement * p_root_element = p_doc->RootElement();
		REQUIRE( p_root_element != nullptr );

		tinyxml2::XMLElement * p_windows = p_doc->NewElement("Windows");

		tinyxml2::XMLElement * p_child_element = p_doc->NewElement("Node_Viewer");
		add_element_property( p_child_element, "Node Viewer", false );

		tinyxml2::XMLElement * p_child2_element = p_doc->NewElement("World_Wonder");
		add_element_property( p_child2_element, "World Wonder", true );

		p_windows->LinkEndChild( p_child_element );
		p_windows->LinkEndChild( p_child2_element );

		p_root_element->LinkEndChild( p_windows );

		WHEN("find a child")
		{
			std::string name = "World_Wonder";
			tinyxml2::XMLElement * p_windows_element = p_root_element->FirstChildElement();
			REQUIRE( strcmp( p_windows_element->Name(), "Windows" ) == 0 );

			tinyxml2::XMLElement * p_cur_node = p_windows_element->FirstChildElement();

			while( nullptr != p_cur_node )
			{
 				if ( strcmp( p_cur_node->Value(), name.c_str() ) == 0 )
				{
 					break;
				}

 				p_cur_node = p_cur_node->NextSiblingElement();
			}

			THEN( "World Wonder?" )
			{
				REQUIRE( p_cur_node != nullptr );
				REQUIRE( strcmp( p_cur_node->Value(), name.c_str() ) == 0 );
			}
		}

		WHEN("add a child")
		{
			tinyxml2::XMLElement * p_another_child = p_doc->NewElement("");
		}

		delete p_doc;
	}
}