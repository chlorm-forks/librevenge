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

#ifndef WP6ATTRIBUTEGROUP_H
#define WP6ATTRIBUTEGROUP_H

#include "WP6FixedLengthGroup.h"

class WP6AttributeGroup : public WP6FixedLengthGroup
{
 public:
	WP6AttributeGroup(GsfInput *input);	
	virtual void parse(WP6LLListener *llListener) = 0;
	const guint8 getAttribute() const { return m_attribute; }
	
 protected:
	virtual void _readContents(GsfInput *input);

 private:
	guint8 m_attribute;
};

class WP6AttributeOnGroup : public WP6AttributeGroup
{
 public:
	WP6AttributeOnGroup(GsfInput *input);
	virtual void parse(WP6LLListener *llListener);
};

class WP6AttributeOffGroup : public WP6AttributeGroup
{
 public:
	WP6AttributeOffGroup(GsfInput *input);
	virtual void parse(WP6LLListener *llListener);
};

#endif /* WP6ATTRIBUTEGROUP_H */
