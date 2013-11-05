/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2002-2004 Marc Maurer (uwog@uwog.net)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGRAWTEXTGENERATOR_H
#define RVNGRAWTEXTGENERATOR_H

#include <stack>
#include <librevenge/librevenge.h>
#include <librevenge-stream/librevenge-stream.h>

using namespace std;

namespace librevenge
{

enum RVNGRawTextGeneratorCallback
{
    LC_START_DOCUMENT = 0,
    LC_OPEN_PAGE_SPAN,
    LC_OPEN_HEADER_FOOTER,
    LC_OPEN_PARAGRAPH,
    LC_OPEN_SPAN,
    LC_OPEN_SECTION,
    LC_OPEN_ORDERED_LIST_LEVEL,
    LC_OPEN_UNORDERED_LIST_LEVEL,
    LC_OPEN_LIST_ELEMENT,
    LC_OPEN_FOOTNOTE,
    LC_OPEN_ENDNOTE,
    LC_OPEN_TABLE,
    LC_OPEN_TABLE_ROW,
    LC_OPEN_TABLE_CELL,
    LC_OPEN_COMMENT,
    LC_OPEN_TEXT_BOX,
    LC_OPEN_FRAME
};

class RVNGRawTextGenerator : public RVNGTextInterface
{
public:
	explicit RVNGRawTextGenerator(bool printCallgraphScore);
	virtual ~RVNGRawTextGenerator();

	virtual void setDocumentMetaData(const RVNGPropertyList &propList);

	virtual void startDocument();
	virtual void endDocument();

	virtual void definePageStyle(const RVNGPropertyList &propList);
	virtual void openPageSpan(const RVNGPropertyList &propList);
	virtual void closePageSpan();
	virtual void openHeader(const RVNGPropertyList &propList);
	virtual void closeHeader();
	virtual void openFooter(const RVNGPropertyList &propList);
	virtual void closeFooter();

	virtual void defineParagraphStyle(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops);
	virtual void openParagraph(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops);
	virtual void closeParagraph();

	virtual void defineCharacterStyle(const RVNGPropertyList &propList);
	virtual void openSpan(const RVNGPropertyList &propList);
	virtual void closeSpan();

	virtual void defineSectionStyle(const RVNGPropertyList &propList, const RVNGPropertyListVector &columns);
	virtual void openSection(const RVNGPropertyList &propList, const RVNGPropertyListVector &columns);
	virtual void closeSection();

	virtual void insertTab();
	virtual void insertSpace();
	virtual void insertText(const RVNGString &text);
	virtual void insertLineBreak();
	virtual void insertField(const RVNGString &type, const RVNGPropertyList &propList);

	virtual void defineOrderedListLevel(const RVNGPropertyList &propList);
	virtual void defineUnorderedListLevel(const RVNGPropertyList &propList);
	virtual void openOrderedListLevel(const RVNGPropertyList &propList);
	virtual void openUnorderedListLevel(const RVNGPropertyList &propList);
	virtual void closeOrderedListLevel();
	virtual void closeUnorderedListLevel();
	virtual void openListElement(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops);
	virtual void closeListElement();

	virtual void openFootnote(const RVNGPropertyList &propList);
	virtual void closeFootnote();
	virtual void openEndnote(const RVNGPropertyList &propList);
	virtual void closeEndnote();
	virtual void openComment(const RVNGPropertyList &propList);
	virtual void closeComment();
	virtual void openTextBox(const RVNGPropertyList &propList);
	virtual void closeTextBox();

	virtual void openTable(const RVNGPropertyList &propList, const RVNGPropertyListVector &columns);
	virtual void openTableRow(const RVNGPropertyList &propList);
	virtual void closeTableRow();
	virtual void openTableCell(const RVNGPropertyList &propList);
	virtual void closeTableCell();
	virtual void insertCoveredTableCell(const RVNGPropertyList &propList);
	virtual void closeTable();

	virtual void openFrame(const RVNGPropertyList &propList);
	virtual void closeFrame();

	virtual void insertBinaryObject(const RVNGPropertyList &propList, const RVNGBinaryData &data);
	virtual void insertEquation(const RVNGPropertyList &propList, const RVNGString &data);

private:
	int m_indent;
	int m_callbackMisses;
	bool m_atLeastOneCallback;
	bool m_printCallgraphScore;
	stack<RVNGRawTextGeneratorCallback> m_callStack;

	void __indentUp()
	{
		m_indent++;
	}
	void __indentDown()
	{
		if (m_indent > 0) m_indent--;
	}

	void __iprintf(const char *format, ...);
	void __iuprintf(const char *format, ...);
	void __idprintf(const char *format, ...);

};

}

#endif /* RVNGRAWTEXTGENERATOR_H */

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */