#include "catch.hpp"
#include "debug.h"
#include "map/point.h"

#define TEST_TIMES 3

TEST_CASE( "Generating Points", "[Map][Point][Generator]" ) {

    SECTION( "Default Point" ) {
        auto p = Point();
        REQUIRE( p.is2D() );
        REQUIRE( !p.is3D() );
        REQUIRE( !p.is1D() );

        REQUIRE( p.getDimension() == 2 );
        REQUIRE( p.get(_x_) + p.get(_y_) == 0.0 );
        REQUIRE( p.getI(_x_) + p.getI(_y_) == 0 );

        REQUIRE( p.isTypeInteger() );
        REQUIRE( !p.isTypeDouble() );

        REQUIRE( p.getDirection() == _bad_);

    }

    SECTION( "One Dimensional Double Point" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));

        auto p1d = Point(x);
        REQUIRE( !p1d.is2D() );
        REQUIRE( !p1d.is3D() );
        REQUIRE( p1d.is1D() );

        REQUIRE( p1d.getDimension() == 1 );

        REQUIRE( p1d.get(_x_) == x );
        REQUIRE( p1d.getI(_x_) == (int)x );

        REQUIRE( !p1d.isTypeInteger() );
        REQUIRE( p1d.isTypeDouble() );

        REQUIRE( p1d.getDirection() == _bad_);
    }

    SECTION( "Two Dimensional Double Point" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        auto y = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        WARN("what");
        auto p2d = Point(x,y);
        REQUIRE( p2d.is2D() );
        REQUIRE( !p2d.is3D() );
        REQUIRE( !p2d.is1D() );

        REQUIRE( p2d.getDimension() == 2 );
        REQUIRE( p2d.get(_x_) == x );
        REQUIRE( p2d.get(_y_) == y );
        REQUIRE( p2d.getI(_x_) == (int)x );
        REQUIRE( p2d.getI(_y_) == (int)y );

        REQUIRE( !p2d.isTypeInteger() );
        REQUIRE( p2d.isTypeDouble() );

        REQUIRE( p2d.getDirection() == _bad_);
    }

    SECTION( "Three Dimensional Double Point" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        auto y = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        auto z = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));

        auto p3i = Point(x,y);
        REQUIRE( !p3i.is2D() );
        REQUIRE( p3i.is3D() );
        REQUIRE( !p3i.is1D() );

        REQUIRE( p3i.getDimension() == 3 );
        REQUIRE( p3i.get(_x_) == x );
        REQUIRE( p3i.get(_y_) == y );
        REQUIRE( p3i.get(_z_) == z );

        REQUIRE( p3i.getI(_x_) == (int)x );
        REQUIRE( p3i.getI(_y_) == (int)y );
        REQUIRE( p3i.getI(_z_) == (int)z );

        REQUIRE( !p3i.isTypeInteger() );
        REQUIRE( p3i.isTypeDouble() );

        REQUIRE( p3i.getDirection() == _bad_);
    }


    SECTION( "Double Line" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        auto dir = (PointType)GENERATE(take(TEST_TIMES,random(0, 3)));

        auto pli = Point(dir,x);

        REQUIRE( !pli.is2D() );
        REQUIRE( !pli.is3D() );
        REQUIRE( pli.is1D() );

        REQUIRE( pli.getDimension() == 1 );

        REQUIRE( pli.get(dir) == x );
        REQUIRE( pli.getI(dir) == (int)x );

        REQUIRE( !pli.isTypeInteger() );
        REQUIRE( pli.isTypeDouble() );

        REQUIRE( pli.getDirection() == dir);
    }

    SECTION( "Double Line with Negative Direction" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        auto p = Point(-1,3);

        REQUIRE( !p.is2D() );
        REQUIRE( !p.is3D() );
        REQUIRE( p.is1D() );

        REQUIRE( p.getDimension() == 1 );

        REQUIRE( p.get(_x_) == x );
        REQUIRE( p.getI(_x_) == (int)x );

        REQUIRE( !p.isTypeInteger() );
        REQUIRE( p.isTypeDouble() );

        REQUIRE( p.getDirection() == _x_);
    }

    SECTION( "Double Line with Overflow Direction" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100.0, 100.0)));
        auto p = Point(2345,3);

        REQUIRE( !p.is2D() );
        REQUIRE( !p.is3D() );
        REQUIRE( p.is1D() );

        REQUIRE( p.getDimension() == 1 );

        REQUIRE( p.get(_x_) == x );
        REQUIRE( p.getI(_x_) == (int)x );

        REQUIRE( !p.isTypeInteger() );
        REQUIRE( p.isTypeDouble() );

        REQUIRE( p.getDirection() == _x_);
    }

    SECTION( "One Dimensional Int Point" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100, 100)));

        auto p1i = Point(x);
        REQUIRE( !p1i.is2D() );
        REQUIRE( !p1i.is3D() );
        REQUIRE( p1i.is1D() );

        REQUIRE( p1i.getDimension() == 1 );

        REQUIRE( p1i.get(_x_) == x );
        REQUIRE( p1i.getI(_x_) == x );

        REQUIRE( p1i.isTypeInteger() );
        REQUIRE( !p1i.isTypeDouble() );

        REQUIRE( p1i.getDirection() == _bad_);
    }

    SECTION( "Two Dimensional Int Point" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100, 100)));
        auto y = GENERATE(take(TEST_TIMES,random(-100, 100)));

        auto p2i = Point(x,y);
        REQUIRE( p2i.is2D() );
        REQUIRE( !p2i.is3D() );
        REQUIRE( !p2i.is1D() );

        REQUIRE( p2i.getDimension() == 2 );
        REQUIRE( p2i.get(_x_) == x );
        REQUIRE( p2i.get(_y_) == y );
        REQUIRE( p2i.getI(_x_) == x );
        REQUIRE( p2i.getI(_y_) == y );

        REQUIRE( p2i.isTypeInteger() );
        REQUIRE( !p2i.isTypeDouble() );

        REQUIRE( p2i.getDirection() == _bad_);
    }

    SECTION( "Three Dimensional Int Point" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100, 100)));
        auto y = GENERATE(take(TEST_TIMES,random(-100, 100)));
        auto z = GENERATE(take(TEST_TIMES,random(-100, 100)));

        auto p3i = Point(x,y);
        REQUIRE( !p3i.is2D() );
        REQUIRE( p3i.is3D() );
        REQUIRE( !p3i.is1D() );

        REQUIRE( p3i.getDimension() == 3 );
        REQUIRE( p3i.get(_x_) == x );
        REQUIRE( p3i.get(_y_) == y );
        REQUIRE( p3i.get(_z_) == z );

        REQUIRE( p3i.getI(_x_) == x );
        REQUIRE( p3i.getI(_y_) == y );
        REQUIRE( p3i.getI(_z_) == z );

        REQUIRE( p3i.isTypeInteger() );
        REQUIRE( !p3i.isTypeDouble() );

        REQUIRE( p3i.getDirection() == _bad_);
    }

    SECTION( "Int Line" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100, 100)));
        auto dir = (PointType)GENERATE(take(TEST_TIMES,random(0, 3)));

        auto pli = Point(dir,x);

        REQUIRE( !pli.is2D() );
        REQUIRE( !pli.is3D() );
        REQUIRE( pli.is1D() );

        REQUIRE( pli.getDimension() == 1 );

        REQUIRE( pli.get(dir) == x );
        REQUIRE( pli.getI(dir) == x );

        REQUIRE( pli.isTypeInteger() );
        REQUIRE( !pli.isTypeDouble() );

        REQUIRE( pli.getDirection() == dir);
    }

    SECTION( "Int Line with Negative Direction" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100, 100)));
        auto p = Point(-1,3);

        REQUIRE( !p.is2D() );
        REQUIRE( !p.is3D() );
        REQUIRE( p.is1D() );

        REQUIRE( p.getDimension() == 1 );

        REQUIRE( p.get(_x_) == x );
        REQUIRE( p.getI(_x_) == x );

        REQUIRE( p.isTypeInteger() );
        REQUIRE( !p.isTypeDouble() );

        REQUIRE( p.getDirection() == _x_);
    }

    SECTION( "Int Line with Overflow Direction" ) {
        auto x = GENERATE(take(TEST_TIMES,random(-100, 100)));
        auto p = Point(2345,3);

        REQUIRE( !p.is2D() );
        REQUIRE( !p.is3D() );
        REQUIRE( p.is1D() );

        REQUIRE( p.getDimension() == 1 );

        REQUIRE( p.get(_x_) == x );
        REQUIRE( p.getI(_x_) == x );

        REQUIRE( p.isTypeInteger() );
        REQUIRE( !p.isTypeDouble() );

        REQUIRE( p.getDirection() == _x_);
    }

}

TEST_CASE( "Setting Points", "[Map][Point]" ) {

}