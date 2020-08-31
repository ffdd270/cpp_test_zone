//
// Created by nhy20 on 2020-08-31.
//


#include <catch.hpp>
#include <simdjson/simdjson.h>


using namespace simdjson;

SCENARIO("what is simdjson?", "[simdjson]")
{
	GIVEN("a single twitter json")
	{
		dom::parser parser;
		dom::element tweets = parser.load("example_data/twitter.json");

		WHEN("get integer")
		{
			simdjson_result<dom::element> count = tweets["search_metadata"]["count"];
			int64_t to_int_count = count.get_int64();

			THEN(" count is 100 ")
			{
				REQUIRE( to_int_count == 100 );
			}
		}


		WHEN("get metadata and check type.")
		{
			simdjson_result<dom::element> search_metadata = tweets["search_metadata"];

			THEN("search_metadata is not string, not number, but object.")
			{
				REQUIRE( search_metadata.is_string() == false );
				REQUIRE( search_metadata.is_int64() == false );
				REQUIRE( search_metadata.is_object() == true );
			}
		}
	}
}