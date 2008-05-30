#include "marching_squares.hpp"

// legend
// +--+
// |84|
// |12|
// +--+
//
// 0x0  0x1  0x2  0x3
// +--+ +--+ +--+ +--+
// |  | |  | |  | |--|
// |  | |# | | #| |##|
// +--+ +--+ +--+ +--+
//
// 0x4  0x5  0x6  0x7
// +--+ +--+ +--+ +--+
// | #| | #| | #| | #|
// |  | |# | | #| |##|
// +--+ +--+ +--+ +--+
//
// 0x8  0x9  0xA  0xB
// +--+ +--+ +--+ +--+
// |# | |# | |# | |# |
// |  | |# | | #| |##|
// +--+ +--+ +--+ +--+
//
// 0xC  0xD  0xE  0xF
// +--+ +--+ +--+ +--+
// |##| |##| |##| |##|
// |  | |# | | #| |##|
// +--+ +--+ +--+ +--+
//

typedef unsigned char Byte;

// 0 continuing in same direction
// 1 changing direction
// 2 changing direction if closed
// 3 changing direction if open
// _ error this should never happen
#define _ -1
static Byte lookup[16][16] = 
{ // 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
   { 0, 0, 0, 0, 0, _, 0, _, 0, 0, _, _, 0, _, _, _ }, // 0
   { _, _, 1, 1, _, _, _, _, 1, 1, 3, 0, _, _, _, _ }, // 1
   { _, 1, _, 1, 1, 3, 1, 0, _, _, _, _, _, _, _, _ }, // 2
   { _, 1, 1, 0, _, 1, _, 1, _, _, 1, 1, _, _, _, _ }, // 3
   { _, _, 1, _, _, _, 1, _, 1, _, 3, _, 1, _, 0, _ }, // 4
   { _, _, 3, 1, _, _, 1, _, 3, 1, 1, 2, _, _, 2, _ }, // 5
   { _, _, 1, _, 1, 1, 0, 1, _, _, 1, _, _, _, 1, _ }, // 6
   { _, _, 0, 1, _, _, 1, _, _, _, 2, 1, _, _, 1, _ }, // 7
  // 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
   { _, 1, _, _, 1, 3, _, _, _, 1, _, _, 1, 1, _, _ }, // 8
   { _, 1, _, _, _, 1, _, _, 1, 0, 1, 1, _, 1, _, _ }, // 9
   { _, 3, _, 1, 3, 1, 1, 2, _, 1, _, _, 1, 2, _, _ }, // A
   { _, 0, _, 1, _, 2, _, 1, _, 1, _, _, _, 1, _, _ }, // B
   { _, _, _, _, 1, 1, _, _, 1, _, 1, _, 0, 1, 1, _ }, // C
   { _, _, _, _, _, _, _, _, 1, 1, 2, 1, 1, _, 1, _ }, // D
   { _, _, _, _, 1, 2, 1, 1, _, _, _, _, 1, 1, _, _ }, // E
   { _, _, _, 0, _, _, 0, 0, _, 0, _, 0, 0, 0, 0, 0 }, // F
#undef _

void Marching_squares::
trans_state( uint8_t last, uint8_t curr )
{
   m_trans_state.insert( (last << 4 ) | curr );
}

void Marching_squares::
execute( unsigned start_x, unsigned start_y )
{
   m_curr = m_start = point(start_x,start_y);

   m_last_state = get_state();
   if( m_last_state == 0x6 )
   {
   }
   else if ( m_last_state == 0x9 )
   {
   }
   else
   {
      move_point();
   }

   while( m_curr != m_start )
   {
      switch( s_lookup[m_last_state][m_curr_state] )
      {
      }
      uint8_t key = (m_last_state << 4) & m_curr_state;

      std::set<uint8_t>::iterator found;
      found = m_trans_state.find(key);
      if( found != m_trans_state.end() )
      {
         add_point();
      }
      switch( m_last_state )
      {
      case 0x0:
         break;

      case 0x1:
         switch( m_curr_state )
         {
         case 0x4:
         case 0x5:
            add_point_top();
            break;

         case 0x6:
         case 0x7:
            break;

         default:
            assert(false);
            break;
         }

      case 0x2:
         switch( m_curr_state )
         {
         case 0x1:
         case 0x3:
            add_point_right();
            break;

         case 0x9:
         case 0xB:
            break;

         default:
            assert(false);
            break;
         }

      case 0x3:
         switch( m_curr_state )
         {
         case 0x1:
         case 0x9:
         case 0xB:
            add_point_right();
            break;

         case 0x3:
            break;

         default:
            assert(false);
            break;
         }

      case 0x4:
         switch( m_curr_state )
         {
         case 0x8:
         case 0xC:
            add_point_left();
            break;

         case 0x9:
         case 0xD:
            break;

         default:
            assert(false);
            break;
         }

      case 0x5:
         switch( m_curr_state )
         {
         case 0x4:
         case 0x6:
         case 0x7:
            add_point_top();
            break;

         case 0x5:
            break;

         default:
            assert(false);
            break;
         }

      case 0x6:
         switch( m_curr_state )
         {
         case 0x1:
         case 0x8:
            break;

         case 0x3:
         case 0xB:
            add_point_right();
            break;

         case 0x9:
            if( m_last_dir == RIGHT )
               { add_point_left(); }
            else if( m_last_dir == LEFT )
               { add_point_right; }
            else
               { assert(false); }
            break;

         case 0xC:
         case 0xD:
            add_point_left();
            break;

         default:
            assert(false);
            break;
         }

      case 0x7:
         switch( m_curr_state )
         {
            case
         }
         

      default:
         assert(false);
         break;
      }// switch last state
   } // while


   


}
