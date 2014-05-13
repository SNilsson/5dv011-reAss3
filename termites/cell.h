#pragma once

#include "common.h"


/**
 * \brief Represents the state of a grid cell.
 *
 * A cell is either empty, occupied by a wood chip, occupied by a
 * termite, or occupied by both a wood chip and a termite.
 */
struct cell
{
    /**
     * \brief Flag that is true if the cell is occupied by a termite.
     *
     * Note: At most one termite can occupy a cell at any given time.
     */
    bool occupied_by_termite;

    /**
     * \brief Flag that is true if the cell is occupied by a wood chip.
     *
     * Note: At most one wood chip can occupy a cell at any given time.
     */
    bool occupied_by_chip;
};



/**
 * \brief Creates an empty cell.
 *
 * \param [out] cell
 */
void cell_create( struct cell *cell );


/**
 * \brief Destroys a cell.
 *
 * \param [in,out] cell
 */
void cell_destroy( struct cell *cell );


/**
 * \brief Place a wood chip in the cell.
 *
 * \param [in,out] cell
 */
void cell_place_wood_chip( struct cell *cell );


/**
 * \brief Place a termite in the cell.
 *
 * \param [in,out] cell
 */
void cell_place_termite( struct cell *cell );


/**
 * \brief Returns true if there is a wood chip in the cell.
 *
 * \param [in] cell
 *
 * \return True if the cell is occupied by a wood chip.
 */
bool cell_has_wood_chip( const struct cell *cell );


/**
 * \brief Returns true if there is a termite in the cell.
 *
 * \param [in] cell
 *
 * \return True if the cell is occupied by a termite.
 */
bool cell_has_termite( const struct cell *cell );


/**
 * \brief Removes the wood chip from a cell.
 *
 * \param [in,out] cell
 */
void cell_remove_wood_chip( struct cell *cell );


/**
 * \brief Removes the termite from a cell.
 *
 * \param [in,out] cell
 */
void cell_remove_termite( struct cell *cell );
