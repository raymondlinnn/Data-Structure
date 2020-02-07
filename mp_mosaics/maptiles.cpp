/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <map>
//#include "cs225/RGB_HSL.h"

using namespace std;

Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    map< Point<3>, int > map;
    // create the kdtree
    vector<Point<3>> tiles_xyz;
    for (size_t i = 0; i < theTiles.size(); ++i) {
        LUVAPixel temp = theTiles[i].getAverageColor();
        Point<3> temp_point = convertToXYZ(temp);
        map[temp_point] = i;
        tiles_xyz.push_back(temp_point);
    }
    KDTree<3> tree(tiles_xyz);

    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    MosaicCanvas* canvas = new MosaicCanvas(rows, columns);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            LUVAPixel color = theSource.getRegionColor(r, c);
            // find the correct tile for this region
            Point<3> temp_point = convertToXYZ(color);
            temp_point = tree.findNearestNeighbor(temp_point);
            int idx = map[temp_point];
            canvas->setTile(r, c, &theTiles[idx]);
        }
    }
    return canvas;
}
