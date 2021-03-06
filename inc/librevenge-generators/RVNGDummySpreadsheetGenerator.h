/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGDUMMYSPREADSHEETGENERATOR_H
#define RVNGDUMMYSPREADSHEETGENERATOR_H

#include "librevenge-generators-api.h"

#include <librevenge/librevenge.h>

namespace librevenge
{

class REVENGE_GENERATORS_API RVNGDummySpreadsheetGenerator : public RVNGSpreadsheetInterface
{
	// disable copying
	RVNGDummySpreadsheetGenerator(const RVNGDummySpreadsheetGenerator &other);
	RVNGDummySpreadsheetGenerator &operator=(const RVNGDummySpreadsheetGenerator &other);

public:
	RVNGDummySpreadsheetGenerator();
	~RVNGDummySpreadsheetGenerator();

	void setDocumentMetaData(const RVNGPropertyList &propList);

	void startDocument(const RVNGPropertyList &propList);
	void endDocument();

	void defineEmbeddedFont(const RVNGPropertyList &propList);

	// sheet
	void defineSheetNumberingStyle(const RVNGPropertyList &propList);
	void openSheet(const RVNGPropertyList &propList);
	void closeSheet();
	void openSheetRow(const RVNGPropertyList &propList);
	void closeSheetRow();
	void openSheetCell(const RVNGPropertyList &propList);
	void closeSheetCell();

	// chart
	void defineChartStyle(const RVNGPropertyList &propList);
	void openChart(const RVNGPropertyList &propList);
	void closeChart();
	void openChartTextObject(const RVNGPropertyList &propList);
	void closeChartTextObject();
	void openChartPlotArea(const RVNGPropertyList &propList);
	void closeChartPlotArea();
	void insertChartAxis(const RVNGPropertyList &axis);
	void openChartSerie(const librevenge::RVNGPropertyList &series);
	void closeChartSerie();

	void definePageStyle(const RVNGPropertyList &propList);
	void openPageSpan(const RVNGPropertyList &propList);
	void closePageSpan();
	void openHeader(const RVNGPropertyList &propList);
	void closeHeader();
	void openFooter(const RVNGPropertyList &propList);
	void closeFooter();

	void defineParagraphStyle(const RVNGPropertyList &propList);
	void openParagraph(const RVNGPropertyList &propList);
	void closeParagraph();

	void defineCharacterStyle(const RVNGPropertyList &propList);
	void openSpan(const RVNGPropertyList &propList);
	void closeSpan();

	void openLink(const RVNGPropertyList &propList);
	void closeLink();

	void defineSectionStyle(const RVNGPropertyList &propList);
	void openSection(const RVNGPropertyList &propList);
	void closeSection();

	void insertTab();
	void insertSpace();
	void insertText(const RVNGString &text);
	void insertLineBreak();
	void insertField(const RVNGPropertyList &propList);

	void openOrderedListLevel(const RVNGPropertyList &propList);
	void openUnorderedListLevel(const RVNGPropertyList &propList);
	void closeOrderedListLevel();
	void closeUnorderedListLevel();
	void openListElement(const RVNGPropertyList &propList);
	void closeListElement();

	void openFootnote(const RVNGPropertyList &propList);
	void closeFootnote();
	void openEndnote(const RVNGPropertyList &propList);
	void closeEndnote();
	void openComment(const RVNGPropertyList &propList);
	void closeComment();

	void openTextBox(const RVNGPropertyList &propList);
	void closeTextBox();

	void openTable(const RVNGPropertyList &propList);
	void openTableRow(const RVNGPropertyList &propList);
	void closeTableRow();
	void openTableCell(const RVNGPropertyList &propList);
	void closeTableCell();
	void insertCoveredTableCell(const RVNGPropertyList &propList);
	void closeTable();

	void openFrame(const RVNGPropertyList &propList);
	void closeFrame();

	void insertBinaryObject(const RVNGPropertyList &propList);

	// drawing function
	void openGroup(const RVNGPropertyList &propList);
	void closeGroup();

	void defineGraphicStyle(const RVNGPropertyList &propList);
	void drawRectangle(const RVNGPropertyList &propList);
	void drawEllipse(const RVNGPropertyList &propList);
	void drawPolygon(const RVNGPropertyList &propList);
	void drawPolyline(const RVNGPropertyList &propList);
	void drawPath(const RVNGPropertyList &propList);
	void drawConnector(const RVNGPropertyList &propList);

	void insertEquation(const RVNGPropertyList &propList);
};

}

#endif /* RVNGDUMMYSPREADSHEETGENERATOR_H */

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
