/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 1995-2005 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
*/

#ifndef ContentBlockDialog_H
#define ContentBlockDialog_H

#ifdef SUPPORT_VISUAL_ADBLOCK

#include "SimpleDialog.h"
#include "adjunct/quick_toolkit/widgets/Dialog.h"

enum ContentBlockedType
{
	BLOCKED_FILTER = 0,	// regular autogenerated entry
	BLOCKED_EDITED,		// has been edited and should not be created a filter from
	BLOCKED_PREVIOUSLY,	// previous blocked entry, added to the list when entering blocked mode
};

class ContentBlockDialog : public Dialog
{
public:

	ContentBlockDialog(BOOL started_from_menu);
	virtual ~ContentBlockDialog();
	
	Type				GetType()				{return DIALOG_TYPE_CONTENT_BLOCK_ACCEPT;}
	DialogType			GetDialogType()			{return TYPE_OK;}
	const char*			GetWindowName()			{return "Content Block Dialog";}
	const char*			GetHelpAnchor()			{return "contentblock.html";}
	BOOL				GetModality()			{return TRUE;}
	BOOL				GetIsBlocking()			{return TRUE;}
	void				OnInit(); 
	void				OnCancel();
	UINT32				OnOk();
	void				OnClick(OpWidget *widget, UINT32 id);
#ifdef CF_CAP_REMOVED_SIMPLETREEMODEL
	void				Init(DesktopWindow *parent, OpVector<ContentFilterItem> *content_blocked);
#else
	void				Init(DesktopWindow *parent, ContentBlockTreeModel *content_blocked);
#endif // CF_CAP_REMOVED_SIMPLETREEMODEL
	BOOL				GetShowPagesAsTabs()	{return FALSE; /*m_started_from_menu ? FALSE : TRUE;*/}
	INT32				GetButtonCount()		{return 1;}
	void				GetButtonInfo(INT32 index, OpInputAction*& action, OpString& text, BOOL& is_enabled, BOOL& is_default, OpString8& name);

	void				OnMouseEvent(OpWidget *widget, INT32 pos, INT32 x, INT32 y, MouseButton button, BOOL down, UINT8 nclicks);

	// OpWidgetListener
	void OnItemEdited(OpWidget *widget, INT32 pos, INT32 column, OpString& text);
	void OnDragStart(OpWidget* widget, INT32 pos, INT32 x, INT32 y) {}
	void OnItemEditAborted(OpWidget *widget, INT32 pos, INT32 column, OpString& text);

private:
	enum ContentBlockPage
	{
		PageCurrent = 0,
		PageAll
	};

	ContentBlockTreeModel		*m_model;			// the model maintained outside this class
	ContentBlockTreeModel		*m_model_all;		// the model maintained inside this class containing ALL blocked urls
	BOOL						m_started_from_menu;	// if started from menu, only show all blocked urls
};

#ifndef CF_CAP_HAS_CONTENT_BLOCK_FILTER_CREATION

class ContentBlockFilterCreation
{
public:
	ContentBlockFilterCreation(SimpleTreeModel *content_to_block, const URL url);
	virtual ~ContentBlockFilterCreation();

	// the "fixed" filter URLs are returned from this method
	OP_STATUS GetCreatedFilterURLs(SimpleTreeModel& pattern_content_blocked);
	static OP_STATUS CreateFilterFromURL(URL& homeurl, const uni_char *url, OpString& result);

private:
	SimpleTreeModel *m_initial_content_blocked;	// the URLs the user has selected
	URL	m_url;										// the url of the page
};
#endif // CF_CAP_HAS_CONTENT_BLOCK_FILTER_CREATION
#endif // SUPPORT_VISUAL_ADBLOCK
#endif // BTConfigDialog_H
