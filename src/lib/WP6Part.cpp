/* libwpd2
 * Copyright (C) 2002 William Lachance (wlach@interlog.com)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WPXPart.h"
#include "WP6Part.h"
#include "WP6Header.h"
#include "WP6VariableLengthGroup.h"
#include "WP6FixedLengthGroup.h"
#include "libwpd_internal.h"

// constructPart: constructs a parseable low-level representation of part of the document
// returns the part if it successfully creates the part, returns NULL if it can't
// throws an exception if there is an error
// precondition: readVal us between 0x80 and 0xFF
WP6Part * WP6Part::constructPart(GsfInput *input, guint8 readVal)
{	
	WPD_DEBUG_MSG(("WordPerfect: ConstructPart\n"));
		
	if (readVal >= (guint8)0x80 && readVal <= (guint8)0xCF)
		{
			WPD_DEBUG_MSG(("WordPerfect: constructFixedLengthGroup(input, val)\n"));
			return WP6FixedLengthGroup::constructFixedLengthGroup(input, readVal);
		}
	else if (readVal >= (guint8)0xD0 && readVal <= (guint8)0xEF)
		{
			WPD_DEBUG_MSG(("WordPerfect: constructVariableLengthGroup(input, val)\n"));
			return WP6VariableLengthGroup::constructVariableLengthGroup(input, readVal);
		}      
	else if (readVal >= (guint8)0xF0 && readVal <= (guint8)0xFF)
		{
			WPD_DEBUG_MSG(("WordPerfect: constructFixedLengthGroup(input, val)\n"));
			return WP6FixedLengthGroup::constructFixedLengthGroup(input, readVal);
		}

	WPD_DEBUG_MSG(("WordPerfect: Returning NULL from constructPart\n"));
	return NULL;

	/*
	// flush any remaining text 
	WPD_CHECK_INTERNAL_ERROR(wp6_flush_text(wordperfect_state, wordperfect_parse_struct));
	;*/
}
