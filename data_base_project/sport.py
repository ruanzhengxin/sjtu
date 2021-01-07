# -*- coding: utf-8 -*-

###########################################################################
## Python code generated with wxFormBuilder (version Oct 26 2018)
## http://www.wxformbuilder.org/
##
## PLEASE DO *NOT* EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

###########################################################################
## Class MyFrame
###########################################################################

class MyFrame ( wx.Frame ):

	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"运动会数据库管理系统", pos = wx.DefaultPosition, size = wx.Size( 826,517 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )

		self.SetSizeHints( wx.DefaultSize, wx.DefaultSize )
		self.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BACKGROUND ) )
		self.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INACTIVECAPTION ) )

		bSizer = wx.BoxSizer( wx.VERTICAL )

		sbSizer2 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"操作" ), wx.VERTICAL )

		bSizer5 = wx.BoxSizer( wx.HORIZONTAL )

		self.m_staticText11 = wx.StaticText( sbSizer2.GetStaticBox(), wx.ID_ANY, u"查询/删除条件：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText11.Wrap( -1 )

		bSizer5.Add( self.m_staticText11, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		m_choiceChoices = [ u"项目编号", u"项目名称", u"运动员编号", u"运动员姓名" ]
		self.m_choice = wx.Choice( sbSizer2.GetStaticBox(), wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, m_choiceChoices, wx.CB_SORT )
		self.m_choice.SetSelection( 0 )
		bSizer5.Add( self.m_choice, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_input = wx.TextCtrl( sbSizer2.GetStaticBox(), wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer5.Add( self.m_input, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_button2 = wx.Button( sbSizer2.GetStaticBox(), wx.ID_ANY, u"删除", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer5.Add( self.m_button2, 0, wx.ALL, 5 )

		self.m_button3 = wx.Button( sbSizer2.GetStaticBox(), wx.ID_ANY, u"查询", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer5.Add( self.m_button3, 0, wx.ALL, 5 )


		sbSizer2.Add( bSizer5, 1, wx.ALIGN_CENTER, 5 )


		bSizer.Add( sbSizer2, 0, wx.ALIGN_CENTER, 5 )

		sbSizer3 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"输入" ), wx.HORIZONTAL )

		fgSizer1 = wx.FlexGridSizer( 0, 4, 0, 0 )
		fgSizer1.SetFlexibleDirection( wx.BOTH )
		fgSizer1.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )

		self.m_staticText13 = wx.StaticText( sbSizer3.GetStaticBox(), wx.ID_ANY, u"运动员编号", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText13.Wrap( -1 )

		fgSizer1.Add( self.m_staticText13, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_staticText15 = wx.StaticText( sbSizer3.GetStaticBox(), wx.ID_ANY, u"项目编号", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText15.Wrap( -1 )

		fgSizer1.Add( self.m_staticText15, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_staticText16 = wx.StaticText( sbSizer3.GetStaticBox(), wx.ID_ANY, u"成绩", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText16.Wrap( -1 )

		fgSizer1.Add( self.m_staticText16, 0, wx.ALIGN_CENTER|wx.ALL, 5 )


		fgSizer1.Add( ( 0, 0), 1, wx.EXPAND, 5 )

		self.m_no = wx.TextCtrl( sbSizer3.GetStaticBox(), wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer1.Add( self.m_no, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_event = wx.TextCtrl( sbSizer3.GetStaticBox(), wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer1.Add( self.m_event, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_score = wx.TextCtrl( sbSizer3.GetStaticBox(), wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer1.Add( self.m_score, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

		self.m_button6 = wx.Button( sbSizer3.GetStaticBox(), wx.ID_ANY, u"插入/更新", wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer1.Add( self.m_button6, 0, wx.ALL, 5 )


		sbSizer3.Add( fgSizer1, 1, 0, 5 )


		bSizer.Add( sbSizer3, 0, wx.ALIGN_CENTER_HORIZONTAL, 5 )

		bSizer7 = wx.BoxSizer( wx.HORIZONTAL )

		sbSizer4 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"查询结果" ), wx.HORIZONTAL )

		bSizer51 = wx.BoxSizer( wx.HORIZONTAL )

		self.m_output = wx.TextCtrl( sbSizer4.GetStaticBox(), wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( 500,250 ), wx.TE_MULTILINE )
		bSizer51.Add( self.m_output, 0, wx.ALL, 5 )


		sbSizer4.Add( bSizer51, 1, 0, 5 )


		bSizer7.Add( sbSizer4, 0, 0, 0 )

		bSizer8 = wx.BoxSizer( wx.VERTICAL )


		bSizer8.Add( ( 0, 4), 0, wx.EXPAND, 5 )

		self.m_staticText91 = wx.StaticText( self, wx.ID_ANY, u"Powerd by Group 6", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText91.Wrap( -1 )

		bSizer8.Add( self.m_staticText91, 0, wx.ALIGN_CENTER_HORIZONTAL, 5 )

		self.m_bitmap4 = wx.StaticBitmap( self, wx.ID_ANY, wx.Bitmap( u"1.jpg", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.Size( 250,240 ), 0 )
		bSizer8.Add( self.m_bitmap4, 0, wx.ALIGN_CENTER|wx.ALL, 5 )


		bSizer7.Add( bSizer8, 1, wx.EXPAND, 5 )


		bSizer.Add( bSizer7, 0, wx.EXPAND, 5 )


		self.SetSizer( bSizer )
		self.Layout()
		self.m_statusBar = self.CreateStatusBar( 2, wx.STB_SIZEGRIP, wx.ID_ANY )
		self.m_menubar = wx.MenuBar( 0 )
		self.m_menu = wx.Menu()
		self.m_menuItem_quit = wx.MenuItem( self.m_menu, wx.ID_ANY, u"退出", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu.Append( self.m_menuItem_quit )

		self.m_menubar.Append( self.m_menu, u"菜单" )

		self.m_menu_info = wx.Menu()
		self.m_menuItem_ver = wx.MenuItem( self.m_menu_info, wx.ID_ANY, u"版本", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu_info.Append( self.m_menuItem_ver )

		self.m_menubar.Append( self.m_menu_info, u"关于" )

		self.SetMenuBar( self.m_menubar )


		self.Centre( wx.BOTH )

		# Connect Events
		self.m_button2.Bind( wx.EVT_BUTTON, self.delete )
		self.m_button3.Bind( wx.EVT_BUTTON, self.query )
		self.m_button6.Bind( wx.EVT_BUTTON, self.insert_update )
		self.Bind( wx.EVT_MENU, self.exit, id = self.m_menuItem_quit.GetId() )
		self.Bind( wx.EVT_MENU, self.info, id = self.m_menuItem_ver.GetId() )

	def __del__( self ):
		pass


	# Virtual event handlers, overide them in your derived class
	def delete( self, event ):
		event.Skip()

	def query( self, event ):
		event.Skip()

	def insert_update( self, event ):
		event.Skip()

	def exit( self, event ):
		event.Skip()

	def info( self, event ):
		event.Skip()


