/* libwpd2
 * Copyright (C) 2003 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2003 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
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

#include <gsf/gsf-input.h>
#include "WP42Heuristics.h"
#include "WP42FileStructure.h"
#include "libwpd_support.h"
#include "libwpd_internal.h"

WPDConfidence WP42Heuristics::isWP42FileFormat(GsfInput *input, bool partialContent)
{
	int functionGroupCount = 0;
	
	gsf_input_seek(input, 0, G_SEEK_SET);
	
	while (!gsf_input_eof(input))
	{
		guint8 readVal;
		readVal = gsf_le_read_guint8(input);
		
		if (readVal < (guint8)0x20)
		{
			// line breaks et al, skip
		}
		else if (readVal >= (guint8)0x20 && readVal <= (guint8)0x7F)
		{
			// normal ASCII characters, skip			
		}
		else if (readVal >= (guint8)0x80 && readVal <= (guint8)0xBF)
		{
			// single character function codes, skip
		}
		else 
		{
			// multi character function group
			// check that the size constrains are valid, and that every group_member
			// is properly closed at the right place
		
			if (WP42_FUCNTION_GROUP_SIZE[readVal-0xC0] == -1)
			{
				// variable length function group
				
				// skip over all the bytes in the group, and scan for the closing gate
				guint8 readNextVal;
				while (!gsf_input_eof(input))
				{
					readNextVal = gsf_le_read_guint8(input);
					if (readNextVal == readVal)
						break;
				}

				// when passed the complete file, we don't allow for open groups when we've reached EOF
				if (!partialContent && gsf_input_eof(input) && (readNextVal != readVal))
					return WPD_CONFIDENCE_NONE;
				
				functionGroupCount++;
			}
			else
			{
				// fixed length function group
				
				// seek to the position where the closing gate should be
				bool res = gsf_input_seek(input, WP42_FUCNTION_GROUP_SIZE[readVal-0xC0]-2, G_SEEK_CUR);
				// when passed the complete file, we should be able to do that
				if (!partialContent && res)
					return WPD_CONFIDENCE_NONE;
				
				// read the closing gate
				guint8 readNextVal = gsf_le_read_guint8(input);
				if (readNextVal != readVal)
					return WPD_CONFIDENCE_NONE;
				
				functionGroupCount++;
			}
		}
	}	

	// when we get here, the document is in a format that we could import properly.
	
	// if we didn't entcounter a single WP4.2 function group) then be a bit more carefull.
	// this would be the case when passed a plaintext file for example
	if (!functionGroupCount)
		return WPD_CONDIFENCE_LIKELY;
	
	return WPD_CONFIDENCE_EXCELLENT;
}