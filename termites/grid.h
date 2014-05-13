#pragma once

#include "common.h"

#include "cell.h"


/**
 * \brief Represents a rectangular grid with periodic boundaries.
 *
 * The coordinates are 0-based and wrap around. More specifically, the
 * top left coordinate is x=y=0, and the bottom right coordinate is
 * x=width-1, y=height-1. The x-coordinate x=-1 wraps around to
 * x=width-1. The same applies to the other three boundaries.
 */
struct grid
{
    /** \brief The width of the grid. */
    int width;

    /** \brief The height of the grid. */
    int height;

    /**
     * \brief The grid cells. The object cells[ y ][ x ] is the cell
     * in row y and column x.
     */
    struct cell **cells;
};


/**
 * \brief Creates an empty grid of the given size.
 *
 * \param [out] grid 
 *
 * \param [in] width The width of the grid.
 *
 * \param [in] height The height of the grid.
 */
void grid_create( struct grid *grid,
		  int width,
		  int height );


/**
 * \brief Destroys a grid, releasing all resources.
 *
 * \param [in,out] grid 
 */
void grid_destroy( struct grid *grid );


/**
 * \brief Places a termite at the given coordinate.
 *
 * \param [in,out] grid
 *
 * \param [in] x
 *
 * \param [in] y
 */
void grid_place_termite_at( struct grid *grid,
			    int x, 
			    int y );


/**
 * \brief Removes the termite at the given coordinate.
 *
 * \param [in,out] grid
 *
 * \param [in] x
 *
 * \param [in] y
 */
void grid_remove_termite_at( struct grid *grid,
			     int x, 
			     int y );


/**
 * \brief Places a wood chip at the given coordinate.
 *
 * \param [in,out] grid
 *
 * \param [in] x
 *
 * \param [in] y
 */
void grid_place_wood_chip_at( struct grid *grid,
			      int x, 
			      int y );


/**
 * \brief Removes the wood chip at the given coordinate.
 *
 * \param [in,out] grid
 *
 * \param [in] x
 *
 * \param [in] y
 */
void grid_remove_wood_chip_at( struct grid *grid,
			       int x, 
			       int y );


/**
 * \brief Returns true if there is a termite at the given coordinate.
 *
 * \param [in] grid
 *
 * \param [in] x
 *
 * \param [in] y
 *
 * \return True if the cell in row y and column x is occupied by a
 * termite.
 */
bool grid_has_termite_at( const struct grid *grid,
			  int x,
			  int y );


/**
 * \brief Returns true if there is a wood chip at the given coordinate.
 *
 * \param [in] grid
 *
 * \param [in] x
 *
 * \param [in] y
 *
 * \return True if the cell in row y and column x is occupied by a
 * wood chip.
 */
bool grid_has_wood_chip_at( const struct grid *grid,
			    int x,
			    int y );


/**
 * \brief Returns the coordinates for the cell that lies nearest in
 * the given direction to the given cell coordinates.
 *
 * For exampe, if (x,y)=(7,3) and direction=NORTH, then (*x_out)=7 and
 * (*y_out)=2.
 *
 * \param [in] grid The grid defining the range of the coordinates.
 *
 * \param [in] x The input x-coordinate.
 *
 * \param [in] y The input y-coordinate.
 *
 * \param [out] x_out The output x-coordinate.
 *
 * \param [out] y_out The output y-coordinate.
 *
 * \param [in] direction The direction.
 */
void grid_get_coords_in_direction( const struct grid *grid,
				   int x,
				   int y,
				   int *x_out, 
				   int *y_out,
				   enum direction direction );


/**
 * \brief Returns the size of the grid.
 *
 * \param [in] grid
 *
 * \param [out] width
 *
 * \param [out] height
 */
void grid_get_size( const struct grid *grid,
		    int *width,
		    int *height );
