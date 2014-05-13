#include "cell.h"


void cell_create( struct cell *cell )
{
    assert( cell != NULL );

    cell->occupied_by_termite = false;
    cell->occupied_by_chip = false;
}


void cell_destroy( struct cell *cell )
{
    assert( cell != NULL );
}


void cell_place_wood_chip( struct cell *cell )
{
    assert( cell != NULL );
    assert( cell->occupied_by_chip == false );

    cell->occupied_by_chip = true;
}


void cell_place_termite( struct cell *cell )
{
    assert( cell != NULL );
    assert( cell->occupied_by_termite == false );

    cell->occupied_by_termite = true;
}


void cell_remove_wood_chip( struct cell *cell )
{
    assert( cell != NULL );
    assert( cell->occupied_by_chip == true );

    cell->occupied_by_chip = false;
}


void cell_remove_termite( struct cell *cell )
{
    assert( cell != NULL );
    assert( cell->occupied_by_termite == true );

    cell->occupied_by_termite = false;
}


bool cell_has_wood_chip( const struct cell *cell )
{
    assert( cell != NULL );

    return cell->occupied_by_chip;
}


bool cell_has_termite( const struct cell *cell )
{
    assert( cell != NULL );

    return cell->occupied_by_termite;
}
