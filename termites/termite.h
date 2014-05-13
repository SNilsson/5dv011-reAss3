#pragma once

#include "common.h"

#include "grid.h"


/**
 * \brief Represents the state of a termite.
 * 
 * A termite has a position, an orientation, and might carry a wood
 * chip.
 */
struct termite
{
    /** \brief The grid in which the termite wanders. */
    struct grid *grid;

    /** \brief the x-coordinate. */
    int x;

    /** \brief The y-coordinate. */
    int y;

    /** \brief The orientation. */
    enum direction direction;

    /** \brief Flag that is true if the termite carries a wood chip. */
    bool carries_chip;
};


/**
 * \brief Creates a termmite with a given position and direction.
 *
 * The termite does not carry a wood chip initially.
 *
 * \param [out] term The termite to create.
 *
 * \param [in,out] grid The grid in which the termite wanders.
 *
 * \param [in] x The x-coordinate.
 *
 * \param [in] y The y-coordinate.
 *
 * \param [in] direction The direction.
 */
void termite_create( struct termite *term,
		     struct grid *grid,
		     int x,
		     int y, 
		     enum direction direction );


/**
 * \brief Destroys a termite.
 *
 * \param [in,out] term
 */
void termite_destroy( struct termite *term );


/**
 * \brief Advances the termite one time step.
 *
 * \param [in,out] term
 */
void termite_step( struct termite *term );


/**
 * \brief Returns true if the termite is carrying a wood chip.
 *
 * \param [in] term
 *
 * \return True if the termite is currently carrying a wood chip.
 */
bool termite_carries_wood_chip( const struct termite *term );


/**
 * \brief Returns the coordinates of the termite.
 *
 * \param [in] term
 *
 * \param [out] x
 *
 * \param [out] y
 */
void termite_get_coords( const struct termite *term,
			 int *x, 
			 int *y );
