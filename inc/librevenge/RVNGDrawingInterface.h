/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpg
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 * Copyright (C) 2004 Marc Oude Kotte (marc@solcon.nl)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpg.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef __RVNGPAINTINTERFACE_H__
#define __RVNGPAINTINTERFACE_H__

#include "RVNGPropertyList.h"
#include "RVNGPropertyListVector.h"
#include "RVNGBinaryData.h"

class RVNGDrawingInterface
{
public:
	virtual ~RVNGDrawingInterface() {}

	// none of the other callback functions will be called before this function is called
	virtual void startDocument(const RVNGPropertyList &propList) = 0;

	// none of the other callback functions will be called after this function is called
	virtual void endDocument() = 0;

	/**
	Called when all document metadata should be set. This is always the first callback made.
	\param propList Property list for the metadata. May contain:
	\li \c dc:creator
	\li \c dc:language The document's keywords
	\li \c dc:publisher The document's publisher
	\li \c dc:source
	\li \c dc:subject The document's subject
	\li \c dc:type The document's type
	\li \c dcterms:available Date when the document was completed
	\li \c dcterms:issued: Date of the version of the document
	\li \c libwpd:abstract Abstract of the document's contents
	\li \c libwpd:account Account
	\li \c libwpd:address Address
	\li \c libwpd:attachments
	\li \c libwpd:authorization
	\li \c libwpd:bill-to
	\li \c libwpd:blind-copy
	\li \c libwpd:carbon-copy
	\li \c libwpd:checked-by
	\li \c libwpd:client
	\li \c libwpd:comments
	\li \c libwpd:department
	\li \c libwpd:descriptive-name The descriptive name for the document
	\li \c libwpd:descriptive-type The descriptive type for the document
	\li \c libwpd:destination
	\li \c libwpd:disposition
	\li \c libwpd:division
	\li \c libwpd:document-number
	\li \c libwpd:editor
	\li \c libwpd:forward-to
	\li \c libwpd:group
	\li \c libwpd:mail-stop
	\li \c libwpd:matter
	\li \c libwpd:office
	\li \c libwpd:owner
	\li \c libwpd:project
	\li \c libwpd:purpose
	\li \c libwpd:received-from
	\li \c libwpd:recorded-by
	\li \c libwpd:recorded-date Date when the document was recorded
	\li \c libwpd:reference
	\li \c libwpd:revision-notes
	\li \c libwpd:revision-number
	\li \c libwpd:section
	\li \c libwpd:security
	\li \c libwpd:status
	\li \c libwpd:telephone-number
	\li \c libwpd:version-notes
	\li \c libwpd:version-number
	\li \c meta:creation-date Document creation date
	\li \c meta:initial-creator The document's author
	\li \c meta:keyword The document's keywords
	\li \c
	*/
	virtual void setDocumentMetaData(const RVNGPropertyList &propList) = 0;

	virtual void startPage(const RVNGPropertyList &propList) = 0;

	virtual void endPage() = 0;

	virtual void setStyle(const RVNGPropertyList &propList, const RVNGPropertyListVector &gradient) = 0;

	virtual void startLayer(const RVNGPropertyList &propList) = 0;

	virtual void endLayer() = 0;

	virtual void startEmbeddedGraphics(const RVNGPropertyList &propList) = 0;

	virtual void endEmbeddedGraphics() = 0;

	// Different primitive shapes
	virtual void drawRectangle(const RVNGPropertyList &propList) = 0;

	virtual void drawEllipse(const RVNGPropertyList &propList) = 0;

	virtual void drawPolygon(const RVNGPropertyListVector &vertices) = 0;

	virtual void drawPolyline(const RVNGPropertyListVector &vertices) = 0;

	virtual void drawPath(const RVNGPropertyListVector &path) = 0;

	// Embedded binary/raster data
	virtual void drawGraphicObject(const RVNGPropertyList &propList, const RVNGBinaryData &binaryData) = 0;

	// Embedded text object
	virtual void startTextObject(const RVNGPropertyList &propList, const RVNGPropertyListVector &path) = 0;
	virtual void endTextObject() = 0;

	/**
	Called when a TAB character should be inserted
	*/
	virtual void insertTab() = 0;

	/**
	Called when an explicit space should be inserted
	*/
	virtual void insertSpace() = 0;

	/**
	Called when a string of text should be inserted
	\param text A textbuffer encoded as a UTF8 string
	*/
	virtual void insertText(const RVNGString &text) = 0;

	/**
	Called when a line break should be inserted
	*/
	virtual void insertLineBreak() = 0;

	/**
	Called when a field should be inserted. Field types may include:
	\li \c text:page-number Current page number
	\li \c text:page-count Total # of pages in document
	\param propList Defines a set of properties for the field. May contain:
	\li \c style:num-format Type of page number (for page number)
	*/
	virtual void insertField(const RVNGString &type, const RVNGPropertyList &propList) = 0;

	/**
	Called when a new ordered list level should be opened
	\param propList Defines a set of properties for the list. May contain:
	\li \c libwpd:level The level of the list in the hierarchy
	\li \c style:num-format Type of list
	\li \c style:num-prefix Text that comes before the number in the list
	\li \c style:num-suffix Text that comes after the number in the list
	\li \c text:start-value The starting number of the list
	\li \c text:min-label-width The distance between the list label and the actual text, stored in inches
	\li \c text:space-before The indentation level of the lists, stored in inches
	*/
	virtual void openOrderedListLevel(const RVNGPropertyList &propList) = 0;

	/**
	Called when a new unordered list level should be opened
	\param propList Defines a set of properties for the list level. May contain:
	\li \c libwpd:level The level of the list in the hierarchy
	\li \c text:bullet-char The string that should be used as a bullet
	\li \c text:min-label-width The distance between the bullet and the actual text, stored in inches
	\li \c text:space-before The indentation level of the lists, stored in inches
	*/
	virtual void openUnorderedListLevel(const RVNGPropertyList &propList) = 0;

	/**
	Called when an unordered list level should be closed
	*/
	virtual void closeOrderedListLevel() = 0;

	/**
	Called when an ununordered list level should be closed
	*/
	virtual void closeUnorderedListLevel() = 0;

	/**
	Called when a list element should be opened
	\param propList Property list for the paragraph. May contain:
	\li \c fo:text-align The justification of this paragraph (left, center, end, full, or justify)
	\li \c fo:margin-left The left indentation of this paragraph, in inches
	\li \c fo:margin-right The right indentation of this paragraph, in inches
	\li \c fo:margin-top The amount of extra spacing to be placed before the paragraph, in inches
	\li \c fo:margin-bottom The amount of extra spacing to be placed after the paragraph, in inches
	\li \c fo:text-indent The indentation of first line, in inches (difference relative to margin-left)
	\li \c fo:line-height The amount of spacing between lines, in number of lines (1.0 is single spacing)
	\li \c fo:break-before Whether this paragraph should be placed in a new column or page (the value is set to column or page if so)
	\param tabStops List of tabstop definitions for the paragraph. If the list is empty, default tabstop definition should be used. Each tab stop may contain:
	\li \c style:type Type of tab (left, right, center, or char)
	\li \c style:char Alingnment character for char aligned tabs
	\li \c style:leader-text The leader character
	\li \c style:position Position of the tab
	*/
	virtual void openListElement(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops) = 0;

	/**
	Called when a list element should be closed
	*/
	virtual void closeListElement() = 0;

	/**
	Called when a new paragraph is opened. This (or openListElement) will always be called before any text or span is placed into the document.
	\param propList Property list for the paragraph. May contain:
	\li \c fo:text-align The justification of this paragraph (left, center, end, full, or justify)
	\li \c fo:margin-left The left indentation of this paragraph, in inches
	\li \c fo:margin-right The right indentation of this paragraph, in inches
	\li \c fo:margin-top The amount of extra spacing to be placed before the paragraph, in inches
	\li \c fo:margin-bottom The amount of extra spacing to be placed after the paragraph, in inches
	\li \c fo:text-indent The indentation of first line, in inches (difference relative to margin-left)
	\li \c fo:line-height The amount of spacing between lines, in number of lines (1.0 is single spacing)
	\li \c fo:break-before Whether this paragraph should be placed in a new column or page (the value is set to column or page if so)
	\param tabStops List of tabstop definitions for the paragraph. If the list is empty, default tabstop definition should be used. Each tab stop may contain:
	\li \c style:type Type of tab (left, right, center, or char)
	\li \c style:char Alingnment character for char aligned tabs
	\li \c style:leader-text The leader character
	\li \c style:position Position of the tab
	*/
	virtual void openParagraph(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops) = 0;

	/**
	Called when a paragraph is closed.
	*/
	virtual void closeParagraph() = 0;

	/**
	Called when a text span is opened
	\param propList Property list for the span. May contain:
	\li \c fo:font-style Font style (italic or normal)
	\li \c fo:font-weight Font style (bold or normal)
	\li \c style:text-line-through-type (double or single, if present)
	\li \c style:text-underline-type (double or single, if present)
	\li \c style:text-outline (true or false)
	\li \c fo:font-variant (small-caps, if present)
	\li \c style:font-name The name of the font used in the span, a text string in ascii
	\li \c fo:font-size The size of the font used in the span, in points (72 points per inch)
	\li \c fo:color The color of the font used in the span (encoded in hex: \#RRGGBB)
	\li \c fo:background-color The background color of the text in the span (encoded in hex: \#RRGGBB)
	\li \c style:text-blinking Whether the text should blink (true or false)
	\li \c fo:text-shadow
	*/
	virtual void openSpan(const RVNGPropertyList &propList) = 0;

	/**
	Called when a text span is closed
	*/
	virtual void closeSpan() = 0;
};

#endif // __RVNGPAINTINTERFACE_H__

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */