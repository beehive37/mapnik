
#include "catch.hpp"

#include <iostream>
#include <mapnik/wkb.hpp>
#include <mapnik/feature.hpp>
#include <mapnik/geometry_is_valid.hpp>
#include <mapnik/geometry_is_simple.hpp>
#include <mapnik/geometry_correct.hpp>
#include <mapnik/feature_factory.hpp>
#include <boost/version.hpp>

TEST_CASE("geometry formats") {

SECTION("wkb") {

    unsigned char sp_valid_blob[] = {
        0x0, 0x1, 0xBC, 0xB, 0x0, 0x0, 0x1F, 0x12, 0xDB, 0xCF, 0xC3, 0xA2, 0x41, 0x41, 0x9D, 0x74, 0xB0, 0x31, 0xE6, 0x34, 0x53, 0x41, 0xDB,
        0x1B, 0xB6, 0x7C, 0xD9, 0xA2, 0x41, 0x41, 0x67, 0xA7, 0xB6, 0xF, 0xF6, 0x34, 0x53, 0x41, 0x7C, 0x6, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0,
        0x0, 0x69, 0x3, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x12, 0x0, 0x0, 0x0, 0xBB, 0x4B, 0x9C, 0x59, 0xD2, 0xA2, 0x41, 0x41, 0x3A, 0xAA,
        0x3F, 0xAE, 0xEB, 0x34, 0x53, 0x41, 0xA2, 0xC2, 0xE4, 0xC6, 0xD1, 0xA2, 0x41, 0x41, 0x4C, 0xFE, 0x6, 0x2B, 0xEC, 0x34, 0x53, 0x41,
        0xEC, 0x65, 0x5F, 0x6, 0xCE, 0xA2, 0x41, 0x41, 0xDD, 0x33, 0x7F, 0x24, 0xEF, 0x34, 0x53, 0x41, 0x2D, 0x35, 0x2D, 0x30, 0xCB, 0xA2,
        0x41, 0x41, 0x4E, 0xA7, 0x88, 0x9, 0xF1, 0x34, 0x53, 0x41, 0x58, 0x2F, 0x12, 0x96, 0xCA, 0xA2, 0x41, 0x41, 0x52, 0xD1, 0xBD, 0xDC,
        0xF0, 0x34, 0x53, 0x41, 0x1F, 0x12, 0xDB, 0xCF, 0xC3, 0xA2, 0x41, 0x41, 0xB9, 0x31, 0xA4, 0xE1, 0xF5, 0x34, 0x53, 0x41, 0x21, 0xBB,
        0x20, 0x6D, 0xC4, 0xA2, 0x41, 0x41, 0x67, 0xA7, 0xB6, 0xF, 0xF6, 0x34, 0x53, 0x41, 0x5A, 0x82, 0x4A, 0xD3, 0xCA, 0xA2, 0x41, 0x41,
        0xA7, 0x85, 0x3D, 0x58, 0xF1, 0x34, 0x53, 0x41, 0x22, 0xB8, 0x3A, 0x7D, 0xCB, 0xA2, 0x41, 0x41, 0x7D, 0x89, 0xA1, 0x8E, 0xF1, 0x34,
        0x53, 0x41, 0xD0, 0x77, 0x3F, 0x80, 0xCF, 0xA2, 0x41, 0x41, 0x57, 0x69, 0x83, 0xC4, 0xEE, 0x34, 0x53, 0x41, 0xA7, 0xF5, 0x8E, 0xF9,
        0xD1, 0xA2, 0x41, 0x41, 0x9A, 0xA2, 0x31, 0xEE, 0xEC, 0x34, 0x53, 0x41, 0x2A, 0xCD, 0xDE, 0x4C, 0xD4, 0xA2, 0x41, 0x41, 0x11, 0x43,
        0xE1, 0xF7, 0xEA, 0x34, 0x53, 0x41, 0xF, 0x89, 0xB1, 0x66, 0xD5, 0xA2, 0x41, 0x41, 0xC8, 0x5D, 0x86, 0xF1, 0xE9, 0x34, 0x53, 0x41,
        0x19, 0xF4, 0x73, 0x63, 0xD7, 0xA2, 0x41, 0x41, 0x7, 0xB1, 0x14, 0x36, 0xE8, 0x34, 0x53, 0x41, 0xDB, 0x1B, 0xB6, 0x7C, 0xD9, 0xA2,
        0x41, 0x41, 0x98, 0xB5, 0xE0, 0x74, 0xE6, 0x34, 0x53, 0x41, 0xC0, 0x3F, 0xC6, 0xAC, 0xD8, 0xA2, 0x41, 0x41, 0x9D, 0x74, 0xB0, 0x31,
        0xE6, 0x34, 0x53, 0x41, 0xF0, 0xB5, 0xB1, 0x53, 0xD5, 0xA2, 0x41, 0x41, 0x97, 0x47, 0xAD, 0x36, 0xE9, 0x34, 0x53, 0x41, 0xBB, 0x4B,
        0x9C, 0x59, 0xD2, 0xA2, 0x41, 0x41, 0x3A, 0xAA, 0x3F, 0xAE, 0xEB, 0x34, 0x53, 0x41, 0xFE };

    unsigned char sp_invalid_blob[] = {
        0x0, 0x1, 0xBC, 0xB, 0x0, 0x0, 0x1F, 0x12, 0xDB, 0xCF, 0xC3, 0xA2, 0x41, 0x41, 0x9D, 0x74, 0xB0, 0x31, 0xE6, 0x34, 0x53, 0x41, 0xDB,
        0x1B, 0xB6, 0x7C, 0xD9, 0xA2, 0x41, 0x41, 0x67, 0xA7, 0xB6, 0xF, 0xF6, 0x34, 0x53, 0x41, 0x7C, 0x6, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0,
        0x0, 0x69, 0x3, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x12, 0x0, 0x0, 0x0, 0xBB, 0x4B, 0x9C, 0x59, 0xD2, 0xA2, 0x41, 0x41, 0x3A, 0xAA,
        0x3F, 0xAE, 0xEB, 0x34, 0x53, 0x41, 0xA2, 0xC2, 0xE4, 0xC6, 0xD1, 0xA2, 0x41, 0x41, 0x4C, 0xFE, 0x6, 0x2B, 0xEC, 0x34, 0x53, 0x41,
        0xEC, 0x65, 0x5F, 0x6, 0xCE, 0xA2, 0x41, 0x41, 0xDD, 0x33, 0x7F, 0x24, 0xEF, 0x34, 0x53, 0x41, 0x2D, 0x35, 0x2D, 0x30, 0xCB, 0xA2,
        0x41, 0x41, 0x4E, 0xA7, 0x88, 0x9, 0xF1, 0x34, 0x53, 0x41, 0x58, 0x2F, 0x12, 0x96, 0xCA, 0xA2, 0x41, 0x41, 0x52, 0xD1, 0xBD, 0xDC,
        0xF0, 0x34, 0x53, 0x41, 0x1F, 0x12, 0xDB, 0xCF, 0xC3, 0xA2, 0x41, 0x41, 0xB9, 0x31, 0xA4, 0xE1, 0xF5, 0x34, 0x53, 0x41, 0x21, 0xBB,
        0x20, 0x6D, 0xC4, 0xA2, 0x41, 0x41, 0x67, 0xA7, 0xB6, 0xF, 0xF6, 0x34, 0x53, 0x41, 0x5A, 0x82, 0x4A, 0xD3, 0xCA, 0xA2, 0x41, 0x41,
        0xA7, 0x85, 0x3D, 0x58, 0xF1, 0x34, 0x53, 0x41, 0x22, 0xB8, 0x3A, 0x7D, 0xCB, 0xA2, 0x41, 0x41, 0x7D, 0x89, 0xA1, 0x8E, 0xF1, 0x34,
        0x53, 0x41, 0xD0, 0x77, 0x3F, 0x80, 0xCF, 0xA2, 0x41, 0x41, 0x57, 0x69, 0x83, 0xC4, 0xEE, 0x34, 0x53, 0x41, 0xA7, 0xF5, 0x8E, 0xF9,
        0xD1, 0xA2, 0x41, 0x41, 0x9A, 0xA2, 0x31, 0xEE, 0xEC, 0x34, 0x53, 0x41, 0x2A, 0xCD, 0xDE, 0x4C, 0xD4, 0xA2, 0x41, 0x41, 0x11, 0x43,
        0xE1, 0xF7, 0xEA, 0x34, 0x53, 0x41, 0xF, 0x89, 0xB1, 0x66, 0xD5, 0xA2, 0x41, 0x41, 0xC8, 0x5D, 0x86, 0xF1, 0xE9, 0x34, 0x53, 0x41,
        0x19, 0xF4, 0x73, 0x63, 0xD7, 0xA2, 0x41, 0x41, 0x7, 0xB1, 0x14, 0x36, 0xE8, 0x34, 0x53, 0x41, 0xDB, 0x1B, 0xB6, 0x7C, 0xD9, 0xA2,
        0x41, 0x41, 0x98, 0xB5, 0xE0, 0x74, 0xE6, 0x34, 0x53, 0x41, 0xC0, 0x3F, 0xC6, 0xAC, 0xD8, 0xA2, 0x41, 0x41, 0x9D, 0x74, 0xB0, 0x31,
        0xE6, 0x34, 0x53, 0x41, 0xF0, 0xB5, 0xB1, 0x53, 0xD5, 0xA2, 0x41, 0x41, 0x97, 0x47, 0xAD, 0x36, 0xE9, 0x34, 0x53, 0x41, 0xBB, 0x4B,
        0x9C, 0x59, 0xD2, 0xA2, 0x41, 0x41, 0x3A, 0xAA, 0x3F, 0xAE, 0xEB, 0x34, 0x53, 0x41 };

    unsigned char sq_valid_blob[] = {
        0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x40 };

    unsigned char sq_invalid_blob[] = {
        0x23, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x40, 0x23 };

    mapnik::context_ptr ctx(new mapnik::context_type);
    mapnik::feature_ptr feature = mapnik::feature_factory::create(ctx, 1);

    // test of parsing wkb geometries
    try {

        // spatialite blob
        mapnik::geometry::geometry<double> geom = mapnik::geometry_utils::from_wkb((const char*)sp_valid_blob,
                                                                               sizeof(sp_valid_blob) / sizeof(sp_valid_blob[0]),
                                                                               mapnik::wkbSpatiaLite);
        // winding order is not correct per OGC so we'll fix it
        mapnik::geometry::correct(geom);
#if BOOST_VERSION >= 105800
        REQUIRE(mapnik::geometry::is_valid(geom));
        REQUIRE(mapnik::geometry::is_simple(geom));
#endif

        geom = mapnik::geometry_utils::from_wkb((const char*)sp_valid_blob,
                                                sizeof(sp_valid_blob) / sizeof(sp_valid_blob[0]),
                                                mapnik::wkbAuto);
        mapnik::geometry::correct(geom);
#if BOOST_VERSION >= 105800
        REQUIRE(mapnik::geometry::is_valid(geom));
        REQUIRE(mapnik::geometry::is_simple(geom));
#endif

        geom = mapnik::geometry_utils::from_wkb((const char*)sp_invalid_blob,
                                                sizeof(sp_invalid_blob) / sizeof(sp_invalid_blob[0]),
                                                mapnik::wkbAuto);
        REQUIRE(geom.is<mapnik::geometry::geometry_empty>()); // returns geometry_empty

        // sqlite generic wkb blob

        geom = mapnik::geometry_utils::from_wkb((const char*)sq_valid_blob,
                                                sizeof(sq_valid_blob) / sizeof(sq_valid_blob[0]),
                                                mapnik::wkbGeneric);
#if BOOST_VERSION >= 105800
        REQUIRE(mapnik::geometry::is_valid(geom));
        REQUIRE(mapnik::geometry::is_simple(geom));
#endif

        geom = mapnik::geometry_utils::from_wkb( (const char*)sq_valid_blob,
                                                 sizeof(sq_valid_blob) / sizeof(sq_valid_blob[0]),
                                                 mapnik::wkbAuto);

#if BOOST_VERSION >= 105800
        REQUIRE(mapnik::geometry::is_valid(geom));
        REQUIRE(mapnik::geometry::is_simple(geom));
#endif

        geom = mapnik::geometry_utils::from_wkb((const char*)sq_invalid_blob,
                                                sizeof(sq_invalid_blob) / sizeof(sq_invalid_blob[0]),
                                                mapnik::wkbGeneric);
        REQUIRE(geom.is<mapnik::geometry::geometry_empty>()); // returns geometry_empty

    }
    catch (std::exception const& ex)
    {
        REQUIRE(false);
        std::clog << "threw: " << ex.what() << "\n";
    }
}
}
