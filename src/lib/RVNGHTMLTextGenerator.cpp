/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002-2004 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2002 Marc Maurer (uwog@uwog.net)
 * Copyright (C) 2004 Fridrich Strba (fridrich.strba@bluewin.ch)
 * Copyright (C) 2005 Net Integration Technologies (http://www.net-itech.com)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#include <stdio.h>
#include <iostream>
#include <librevenge-generators/librevenge-generators.h>

// use the BELL code to represent a TAB for now
#define UCS_TAB 0x0009

namespace librevenge
{

RVNGHTMLTextGenerator::RVNGHTMLTextGenerator() :
	m_ignore(false),
	m_pOutputStream(&std::cout),
	m_footNotesStream(),
	m_endNotesStream(),
	m_commentsStream(),
	m_textBoxesStream(),
	m_dummyStream(),
	m_footNotesCount(0),
	m_endNotesCount(0),
	m_commentsCount(0),
	m_textBoxesCount(0),
	m_commentNumber(1),
	m_textBoxNumber(1)
{
}

RVNGHTMLTextGenerator::~RVNGHTMLTextGenerator()
{
}

void RVNGHTMLTextGenerator::setDocumentMetaData(const RVNGPropertyList &propList)
{
	if (propList["meta:initial-creator"])
		*m_pOutputStream << "<meta name=\"author\" content=\"" << propList["meta:initial-creator"]->getStr().cstr() << "\">" << std::endl;
	if (propList["dc:creator"])
		*m_pOutputStream << "<meta name=\"typist\" content=\"" << propList["dc:creator"]->getStr().cstr() << "\">" << std::endl;
	if (propList["dc:subject"])
		*m_pOutputStream << "<meta name=\"subject\" content=\"" << propList["dc:subject"]->getStr().cstr() << "\">" << std::endl;
	if (propList["dc:publisher"])
		*m_pOutputStream << "<meta name=\"publisher\" content=\"" << propList["dc:publisher"]->getStr().cstr() << "\">" << std::endl;
	if (propList["meta:keyword"])
		*m_pOutputStream << "<meta name=\"keywords\" content=\"" << propList["meta:keyword"]->getStr().cstr() << "\">" << std::endl;
	if (propList["dc:language"])
		*m_pOutputStream << "<meta name=\"language\" content=\"" << propList["dc:language"]->getStr().cstr() << "\">" << std::endl;
	if (propList["dc:description"])
		*m_pOutputStream << "<meta name=\"abstract\" content=\"" << propList["dc:description"]->getStr().cstr() << "\">" << std::endl;
	if (propList["librevenge:descriptive-name"])
	{
		*m_pOutputStream << "<meta name=\"descriptive-name\" content=\"" << propList["librevenge:descriptive-name"]->getStr().cstr() << "\">" << std::endl;
		*m_pOutputStream << "<title>" << propList["librevenge:descriptive-name"]->getStr().cstr() << "</title>" << std::endl;
	}
	if (propList["librevenge:descriptive-type"])
		*m_pOutputStream << "<meta name=\"descriptive-type\" content=\"" << propList["librevenge:descriptive-type"]->getStr().cstr() << "\">" << std::endl;
}

void RVNGHTMLTextGenerator::startDocument()
{
	*m_pOutputStream << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\" \"http://www.w3.org/TR/REC-html40/loose.dtd\">" << std::endl;
	*m_pOutputStream << "<html>" << std::endl;
	*m_pOutputStream << "<head>" << std::endl;
	*m_pOutputStream << "<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\" >" << std::endl;
	*m_pOutputStream << "</head>" << std::endl;
	*m_pOutputStream << "<body>" << std::endl;
}

void RVNGHTMLTextGenerator::endDocument()
{
	if (m_footNotesStream.str().length())
	{
		*m_pOutputStream << "<p><b>FOOTNOTES</b></p>" << std::endl;
		*m_pOutputStream << m_footNotesStream.str() << std::endl;
	}
	if (m_endNotesStream.str().length())
	{
		*m_pOutputStream << "<p><b>ENDNOTES</b></p>" << std::endl;
		*m_pOutputStream << m_endNotesStream.str() << std::endl;
	}
	if (m_commentsStream.str().length())
	{
		*m_pOutputStream << "<p><b>COMMENTS AND ANNOTATIONS</b></p>" << std::endl;
		*m_pOutputStream << m_commentsStream.str() << std::endl;
	}
	if (m_textBoxesStream.str().length())
	{
		*m_pOutputStream << "<p><b>TEXT BOXES</b></p>" << std::endl;
		*m_pOutputStream << m_textBoxesStream.str() << std::endl;
	}
	*m_pOutputStream << "</body>" << std::endl;
	*m_pOutputStream << "</html>" << std::endl;
}

void RVNGHTMLTextGenerator::openHeader(const RVNGPropertyList & /* propList */)
{
	m_ignore = true;
}

void RVNGHTMLTextGenerator::closeHeader()
{
	m_ignore = false;
}


void RVNGHTMLTextGenerator::openFooter(const RVNGPropertyList & /* propList */)
{
	m_ignore = true;
}

void RVNGHTMLTextGenerator::closeFooter()
{
	m_ignore = false;
}

void RVNGHTMLTextGenerator::openParagraph(const RVNGPropertyList &propList, const RVNGPropertyListVector & /* tabStops */)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<p style=\"";

		if (propList["fo:text-align"])
		{

			if (propList["fo:text-align"]->getStr() == RVNGString("end")) // stupid OOo convention..
				*m_pOutputStream << "text-align:right;";
			else
				*m_pOutputStream << "text-align:" << propList["fo:text-align"]->getStr().cstr() << ";";
		}
		if (propList["fo:text-indent"])
			*m_pOutputStream << "text-indent:" << propList["fo:text-indent"]->getStr().cstr() << ";";

		if (propList["fo:line-height"] && propList["fo:line-height"]->getDouble() != 1.0)
			*m_pOutputStream << "line-height:" << propList["fo:line-height"]->getDouble() << ";";
		*m_pOutputStream << "\">";
	}
}

void RVNGHTMLTextGenerator::closeParagraph()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</p>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::openSpan(const RVNGPropertyList &propList)
{
	if (!m_ignore)
	{

		*m_pOutputStream << "<span style=\"";
		if (propList["style:font-name"])
			*m_pOutputStream << "font-family: \'" << propList["style:font-name"]->getStr().cstr() << "\';";
		if (propList["fo:font-size"])
			*m_pOutputStream << "font-size: " << propList["fo:font-size"]->getStr().cstr() << ";";
		if (propList["fo:font-weight"])
			*m_pOutputStream << "font-weight: " << propList["fo:font-weight"]->getStr().cstr() << ";";
		if (propList["fo:font-style"])
			*m_pOutputStream << "font-style: " << propList["fo:font-style"]->getStr().cstr() << ";";
		if (propList["style:text-crossing-out"] && propList["style:text-crossing-out"]->getStr() == RVNGString("single-line"))
			*m_pOutputStream << "text-decoration:line-through;";
		if (propList["style:text-underline"]) // don't know if double underline is possible
			*m_pOutputStream << "text-decoration:underline;";
		if (propList["style:text-blinking"])
			*m_pOutputStream << "text-decoration:blink;";
		if (propList["fo:color"])
			*m_pOutputStream << "color:" << propList["fo:color"]->getStr().cstr() << ";";
		if (propList["style:text-background-color"])
			*m_pOutputStream << "background-color:" << propList["style:text-background-color"]->getStr().cstr() << ";";

		*m_pOutputStream << "\">";
	}
}

void RVNGHTMLTextGenerator::closeSpan()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</span>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::insertTab()
{
	if (!m_ignore)
	{
		// Does not have a lot of effect since tabs in html are ignorable white-space
		*m_pOutputStream << "\t";
	}
}

void RVNGHTMLTextGenerator::insertLineBreak()
{
	if (!m_ignore)
	{

		*m_pOutputStream << "<br>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::insertText(const RVNGString &text)
{
	if (!m_ignore)
	{

		RVNGString tempUTF8(text, true);
		*m_pOutputStream << tempUTF8.cstr();
	}
}

void RVNGHTMLTextGenerator::insertSpace()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "&nbsp;";
	}
}

void RVNGHTMLTextGenerator::openOrderedListLevel(const RVNGPropertyList & /* propList */)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<ol>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::closeOrderedListLevel()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</ol>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::openUnorderedListLevel(const RVNGPropertyList & /* propList */)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<ul>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::closeUnorderedListLevel()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</ul>" << std::endl;
	}
}


void RVNGHTMLTextGenerator::openListElement(const RVNGPropertyList & /* propList */, const RVNGPropertyListVector &/* tabStops */)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<li>";
	}
}

void RVNGHTMLTextGenerator::closeListElement()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</li>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::openFootnote(const RVNGPropertyList &propList)
{
	if (!m_ignore)
	{
		if (!m_footNotesCount++)
		{
			if (propList["librevenge:number"])
				*m_pOutputStream << "<sup>(footnote: " << propList["librevenge:number"]->getStr().cstr() << ")</sup>";
			m_pOutputStream = &m_footNotesStream;
			// Cheesey hack..
			if (propList["librevenge:number"])
				*m_pOutputStream << "<p>" << propList["librevenge:number"]->getStr().cstr() << ":</p>";
			else
				*m_pOutputStream << "<p/>";
		}
		else
			m_pOutputStream = &m_dummyStream;
	}
}

void RVNGHTMLTextGenerator::closeFootnote()
{
	if (!m_ignore)
	{
		if (!(--m_footNotesCount))
		{
			*m_pOutputStream << "<p/>" << std::endl;
			m_pOutputStream = &std::cout;
		}
	}
}

void RVNGHTMLTextGenerator::openEndnote(const RVNGPropertyList &propList)
{
	if (!m_ignore)
	{
		if (!m_endNotesCount++)
		{
			if (propList["librevenge:number"])
				*m_pOutputStream << "<sup>(endnote: " << propList["librevenge:number"]->getStr().cstr() << ")</sup>";
			m_pOutputStream = &m_footNotesStream;
			// Cheesey hack..
			if (propList["librevenge:number"])
				*m_pOutputStream << "<p>" << propList["librevenge:number"]->getStr().cstr() << ":</p>";
			else
				*m_pOutputStream << "<p/>";
		}
		else
			m_pOutputStream = &m_dummyStream;
	}
}

void RVNGHTMLTextGenerator::closeEndnote()
{
	if (!m_ignore)
	{
		if (!(--m_endNotesCount))
		{
			*m_pOutputStream << "<p/>" << std::endl;
			m_pOutputStream = &std::cout;
		}
	}
}

void RVNGHTMLTextGenerator::openComment(const RVNGPropertyList & /*propList*/)
{
	if (!m_ignore)
	{
		if (!m_commentsCount++)
		{
			*m_pOutputStream << "<sup>(comment: " << m_commentNumber << ")</sup>";
			m_pOutputStream = &m_commentsStream;
			*m_pOutputStream << "<p>Comment " << m_commentNumber++ << ":</p>" << std::endl;
			*m_pOutputStream << "<p/>";
		}
		else
			m_pOutputStream = &m_dummyStream;
	}
}

void RVNGHTMLTextGenerator::closeComment()
{
	if (!m_ignore)
	{
		if (!(--m_commentsCount))
		{
			*m_pOutputStream << "<p/>" << std::endl;
			m_pOutputStream = &std::cout;
		}
	}
}

void RVNGHTMLTextGenerator::openTextBox(const RVNGPropertyList & /*propList*/)
{
	if (!m_ignore)
	{
		if (!m_textBoxesCount++)
		{
			*m_pOutputStream << "<sup>(text box: " << m_textBoxNumber << ")</sup>";
			m_pOutputStream = &m_commentsStream;
			*m_pOutputStream << "<p>Text Box " << m_textBoxNumber++ << ":</p>" << std::endl;
			m_pOutputStream = &m_textBoxesStream;
			*m_pOutputStream << "<p/>";
		}
		else
			m_pOutputStream = &m_dummyStream;
	}
}

void RVNGHTMLTextGenerator::closeTextBox()
{
	if (!m_ignore)
	{
		if (!(--m_textBoxesCount))
		{
			*m_pOutputStream << "<p/>" << std::endl;
			m_pOutputStream = &std::cout;
		}
	}
}

void RVNGHTMLTextGenerator::openTable(const RVNGPropertyList & /* propList */, const RVNGPropertyListVector & /* columns */)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<table border=\"1\">" << std::endl;
		*m_pOutputStream << "<tbody>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::openTableRow(const RVNGPropertyList & /* propList */)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<tr>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::closeTableRow()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</tr>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::openTableCell(const RVNGPropertyList &propList)
{
	if (!m_ignore)
	{
		*m_pOutputStream << "<td style=\"";
		if (propList["fo:background-color"])
			*m_pOutputStream << "background-color:" << propList["fo:background-color"]->getStr().cstr() << ";";

		*m_pOutputStream << "\" ";

		if (propList["table:number-columns-spanned"])
			*m_pOutputStream << "colspan=\"" << propList["table:number-columns-spanned"]->getInt() << "\" ";
		if (propList["table:number-rows-spanned"])
			*m_pOutputStream << "rowspan=\"" << propList["table:number-rows-spanned"]->getInt() << "\" ";

		*m_pOutputStream << ">" << std::endl;
	}
}

void RVNGHTMLTextGenerator::closeTableCell()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</td>" << std::endl;
	}
}

void RVNGHTMLTextGenerator::closeTable()
{
	if (!m_ignore)
	{
		*m_pOutputStream << "</tbody>" << std::endl;
		*m_pOutputStream << "</table>" << std::endl;
	}
}

}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */