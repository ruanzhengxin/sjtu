import sys
import pymysql
import wx

'''
处理数据库类
'''

class database:
    def __init__(self):
        self.con = pymysql.connect(host='localhost',user='root',passwd='456rzx123',db='111')
        self.cursor = self.con.cursor()

    def insert(self,event):
        table = Input.GetValue()
        info = Info.GetValue()
        sql = "insert into " + table + " values(" +info + ")"
        self.cursor.execute(sql)
        self.con.commit()

    def select_id(self,id):
        table = Input.GetValue()
        id=Info.GetValue()
        sql = "select * from "+ table +" where Aname = %s"
        self.cursor.execute(sql,id)
        result = self.cursor.fetchall()
        for var in result:
            for item in var:
                contents.AppendText(str(item) + ' , ')
            contents.AppendText('\n')

    def show(self,event):
        table = Input.GetValue()
        sql = "select * from "+ table
        self.cursor.execute(sql)
        result = self.cursor.fetchall()
        contents.AppendText("That's all the data in table "+table+' \n')
        for var in result:
            for item in var:
                contents.AppendText(str(item)+' , ')            
            contents.AppendText('\n')

    def inset_grade(self,event):
        Ano=Input1.GetValue()
        Gno=Input2.GetValue()
        grade=Input3.GetValue()
        self.cursor.execute('insert into join values(Ano,Gno,grade)')
        self.con.commit()

    def select(self,Ano):
        sql = "select a.Aname,join.Gno,join.grade from a JOIN join ON a.Ano=join.Ano where a.Ano = " + Ano
        self.cursor.execute(sql)
        result = cursor.fetchall()
        contents.SetValue(result)

    def order(self,Gno):
        sql = "select * from join where Gno="+ Gno +"order by grade asc"
        self.cursor.execute(sql)
        result = cursor.fetchall()
        contents.SetValue(result)
def help(event):
    contents.AppendText("the first TextBox is thblename\n")
    contents.AppendText("the second TextBox is the infomation you want to add\n")

if __name__ == '__main__':
    solve = database()

    try:
        app = wx.App()

        win = wx.Frame(None,title='DataBase',size=(410,335))

        bkg = wx.Panel(win)

        showButton = wx.Button(bkg,label = 'Show')
        showButton.Bind(wx.EVT_BUTTON,solve.show)
        helpButton = wx.Button(bkg,label = 'Help')
        helpButton.Bind(wx.EVT_BUTTON,help)
        insertButton = wx.Button(bkg,label = 'Insert')
        insertButton.Bind(wx.EVT_BUTTON,solve.insert)
        selectButton = wx.Button(bkg,label = 'Select')
        selectButton.Bind(wx.EVT_BUTTON,solve.select_id)
        Input = wx.TextCtrl(bkg)
        contents = wx.TextCtrl(bkg,style = wx.TE_MULTILINE | wx.HSCROLL)
        Info = wx.TextCtrl(bkg)
        hbox = wx.BoxSizer()
        hbox.Add(Input, proportion=1,flag = wx.EXPAND)
        hbox.Add(Info, proportion=2,flag = wx.EXPAND)
        hbox.Add(showButton, proportion=0, flag=wx.LEFT, border=5)
        hbox.Add(insertButton, proportion=0, flag=wx.LEFT, border=5)
        hbox.Add(selectButton, proportion=0, flag=wx.LEFT, border=5)
        hbox.Add(helpButton, proportion=0, flag=wx.LEFT, border=5)

        vbox=wx.BoxSizer(wx.VERTICAL)
        vbox.Add(hbox, proportion=0, flag=wx.EXPAND | wx.ALL, border=5)
        vbox.Add(contents, proportion=1, flag = wx.EXPAND | wx.LEFT | wx.BOTTOM |           wx.RIGHT, border=5)

        bkg.SetSizer(vbox)

        win.Show()

        app.MainLoop()

    finally:
        solve.cursor.close()
        solve.con.close()
