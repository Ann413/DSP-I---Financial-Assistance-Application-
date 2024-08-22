
from tkinter import *
from tkinter import messagebox
from tkinter import ttk
from PIL import Image, ImageTk

class FirstPage(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)

        self.config(bg='#fff')

        self.img = PhotoImage(file='login.png')
        Label(self, image=self.img, bg='white').place(x=80, y=80)

        frame = Frame(self, width=350, height=350, bg='white')
        frame.place(x=650, y=130)

        heading = Label(frame, text='Sign in', fg='#57a1f8', bg='white', font=('Microsoft YaHei UI Light', 23, 'bold'))
        heading.place(x=115, y=10)

        title = Label(self, text='Financial Assistance Application', bg='white', font=('Arial', 30, 'bold'))
        title.place(x=500, y=38)

#############################################----------------------------------------

        def on_enter(e):
            user.delete(0, 'end')

        def on_leave(e):
            name = user.get()
            if name == '':
                user.insert(0, 'IC Number')

        user = Entry(frame, width=25, fg='black', border=0, bg='white', font=('Microsoft YaHei UI Light', 11))
        user.place(x=30, y=80)
        user.insert(0, 'IC Number')
        user.bind('<FocusIn>', on_enter)
        user.bind('<FocusOut>', on_leave)

        Frame(frame, width=295, height=2, bg='black').place(x=25, y=107)

##############################################-----------------------------------------------------------------------------

        def on_enter(e):
            code.delete(0, 'end')

        def on_leave(e):
            name = code.get()
            if name == '':
                code.insert(0, 'Password')

        code = Entry(frame, width=25, fg='black', border=0, bg='white', font=('Microsoft YaHei UI Light', 11))
        code.place(x=30, y=150)
        code.insert(0, 'Password')
        code.bind('<FocusIn>', on_enter)
        code.bind('<FocusOut>', on_leave)

        Frame(frame, width=295, height=2, bg='black').place(x=25, y=177)

##############################-----------------------------------------------

        def verify():
            try:
                with open('credential.txt', 'r') as f:
                    info = f.readlines()
                    i = 0
                    for e in info:
                        u, p = e.split(',')
                        if u.strip() == user.get() and p.strip() == code.get():
                            controller.show_frame(ThirdPage)
                            i = 1
                            break
                    if i == 0:
                        messagebox.showinfo('Error', 'Please provide correct IC Number and password!')
            except:
                messagebox.showinfo('Error', 'Please provide correct IC Number and password!')

        Button(frame, width=39, pady=7, text='Sign in', bg='#57a1f8', fg='white', border=0, command=verify).place(x=35, y=204)
        label = Label(frame, text="Don't have an account?", fg='black', bg='white',font=('Microsoft YaHei UI Light', 9))
        label.place(x=75, y=270)

        def register():
            controller.show_frame(SecondPage)

        sign_up = Button(frame, width=6, text='Sign up', border=0, bg='white', fg='#57a1f8', command=register)
        sign_up.place(x=215, y=270)



class SecondPage(Frame):

    def __init__(self, parent, controller):
        Frame.__init__(self, parent)

        self.config(bg='white')

        img = Image.open('registration.png')
        photo = ImageTk.PhotoImage(img)
        label = Label(self, image=photo)
        label.image=photo
        label.place(x=0, y=0)

        frame = Frame(self, width=950, height=400, bg='white')
        frame.place(x=125, y=70)

        label = Label(frame, text = 'Registration', bg='white', font=('Arial', 30, 'bold'))
        label.place(x=360, y=30)

        l1 = Label(frame, text='IC Number', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l1.place(x=250, y=150)
        user = Entry(frame, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        user.place(x=500, y=150)

        l2 = Label(frame, text='Password', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l2.place(x=250, y=210)
        code = Entry(frame, width=25, fg='black', bd=3, show='*',bg='white', font=('Microsoft YaHei UI Light', 11))
        code.place(x=500, y=210)

        l3 = Label(frame, text='Confirm Password', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l3.place(x=250, y=270)
        confirm = Entry(frame, width=25, fg='black', show='*', bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        confirm.place(x=500, y=270)

        ##############################################-----------------------------------------------------------------------------

        def check():
            if user.get() != '' and code.get() != '' and confirm.get() != '':
                if code.get() == confirm.get():
                    with open('credential.txt', 'a') as f:
                        f.write(user.get() + ',' + code.get() + '\n')
                        messagebox.showinfo('Welcome', 'you are registered successfully!!')
                    controller.show_frame(FirstPage)
                else:
                    messagebox.showinfo('Error', "Your password didn't get match!!")
            else:
                messagebox.showinfo('Error', "Please fill the complete field!!")

        Button(frame, width=39, pady=7, text='Sign up', bg='#57a1f8', fg='white', border=0, command=check).place(x=360,y=350)



##############################-----------------------------------------------


class ThirdPage(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)

        self.config(bg='white')

        label = Label(self, text='Information Application', bg='white', font=('Arial', 30, 'bold'))
        label.place(x=400, y=15)

        f1 = Frame(self, width=570, height=450, bd=2, bg='white')
        f1.place(x=15, y=75)

        f2 = Frame(self, width=570, height=420, bd=2, bg='white')
        f2.place(x=615, y=75)

        l1 = Label(f1, text='IC Number', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l1.place(x=30, y=25)
        e1 = Entry(f1, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e1.place(x=250, y=25)

        l2 = Label(f1, text='Name', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l2.place(x=30, y=85)
        e2 = Entry(f1, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e2.place(x=250, y=85)

        l3 = Label(f1, text='Job', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l3.place(x=30, y=145)
        e3 = Entry(f1, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e3.place(x=250, y=145)

        l4 = Label(f1, text='Allowance', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l4.place(x=30, y=205)
        e4 = Entry(f1, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e4.place(x=250, y=205)

        l5 = Label(f1, text='Address', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l5.place(x=30, y=265)
        e5 = Entry(f1, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e5.place(x=250, y=265)

        l6 = Label(f1, text='Bank Name', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l6.place(x=30, y=325)
        Bank = ['BANK SIMPANAN NASIONAL', 'AFFIN BANK BERHAD', 'ARGO BANK', 'AL RAJHI BANKING INVESTMENT CORPORATION', 'ALLIANCE BANK MALAYSIA BERHAD', 'AM BANK BERHAD', 'BANK ISLAM MALAYSIA BERHAD', 'BANK KERJASAMA RAKYAT MALAYSIA BHD', 'BANK MUAMALAT MALAYSIA BERHAD', 'BANK OF CHINA (MALAYSIA) BERHAD', 'CIMB BANK BERHAD', 'CITIBANK BERHAD', 'HONG LEONG BANK', 'HONGKONG SHANGHAI BANK MALAYSIA BHD', 'KUWAIT FINANCE HOUSE MALAYSIA', 'MALAYAN BANKING BERHAD', 'OCBC AL-AMIN BANK BHD/OCBC BANK MALAYSIA BHD', 'PUBLIC BANK BERHAD/PUBLIC ISLAMIC BANK BERHAD', 'RHB BANK BERHAD']
        e6 = ttk.Combobox(f1, values=Bank, width=31)
        e6.place(x=250, y=325)

        l7 = Label(f1, text='Bank Account Number', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l7.place(x=30, y=385)
        e7 = Entry(f1, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e7.place(x=250, y=385)

        ##########################-------------------------------------------------------------------------------------------

        l8 = Label(f2, text='Age', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l8.place(x=30, y=25)
        e8 = Entry(f2, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e8.place(x=250, y=25)

        l9 = Label(f2, text='Gender', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l9.place(x=30, y=85)
        v=StringVar()
        e9 = Radiobutton(f2, text='Male', variable=v, value='Male', bg='white')
        e9.place(x=250, y=85)
        e9 = Radiobutton(f2, text='Female', variable=v, value='Female', bg='white')
        e9.place(x=335, y=85)


        l10 = Label(f2, text='Marial Status', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l10.place(x=30, y=145)
        marial = ['single', 'married', 'divorced', 'widowed']
        e10 = ttk.Combobox(f2, values=marial, width=31)
        e10.place(x=250, y=145)

        l11 = Label(f2, text='Number of children', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l11.place(x=30, y=205)
        e11 = Spinbox(f2, from_=0, to=15, width=32)
        e11.place(x=250, y=205)

        l12 = Label(f2, text='Contact Number', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l12.place(x=30, y=265)
        e12 = Entry(f2, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e12.place(x=250, y=265)

        l13 = Label(f2, text='Email Address', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l13.place(x=30, y=325)
        e13 = Entry(f2, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        e13.place(x=250, y=325)


        def nextPage():

            if e1.get() != '' and e2.get() != '' and e3.get() != '' and e4.get() != '' and e5.get() != '' and e6.get() != '' and e7.get() != '' and e8.get() != '' and v.get() != '' and e10.get() != '' and e11.get() != '' and e12.get() != '' and e13.get() != '':
                self.user_info = {
                    'username': e2.get(),
                    'ic_number': e1.get()}
                with open('data.txt', 'a') as f:
                    f.write(e1.get() + ',' + e2.get() + ',' + e3.get() + ',' + e4.get() + ',' + e5.get() + ',' + e6.get() + ',' + e7.get() + ',' + e8.get() + ',' + v.get() + ',' + e10.get() + ',' + e11.get() + ',' + e12.get() + ',' + e13.get() + '\n')
                messagebox.showinfo('Welcome', "Submit successfully!!")
                controller.show_frame(FourthPage, self.user_info)
            else:
                messagebox.showinfo('Error', "Please fill the complete field!!")

        Button(self, width=20, pady=8, text='Next', bg='#57a1f8', fg='white', border=0, command=nextPage).place(x=1000,y=500)




class FourthPage(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)

        self.config(bg='white')

        try:
            f1 = Frame(self, width=370, height=350, bd=2, bg='white')
            f1.place(x=15, y=100)

            f2 = Frame(self, width=370, height=350, bd=2, bg='white')
            f2.place(x=415, y=100)

            f3= Frame(self, width=370, height=350, bd=2, bg='white')
            f3.place(x=815, y=100)

            self.img1 = PhotoImage(file='update.png')
            Label(f1, image=self.img1, bg='white').place(x=70, y=20)

            self.img2 = PhotoImage(file='result.png')
            Label(f2, image=self.img2, bg='white').place(x=70, y=20)

            self.img3 = PhotoImage(file='change password.png')
            Label(f3, image=self.img3, bg='white').place(x=70, y=25)

            def result():
                messagebox.showinfo('Status', "Application Accepted, the application will be processed in March 2024")

            def changepass():
                controller.show_frame(FifthPage)

            b1 = Button(f1, text='Edit Application Information', width=25, bg='yellow', font=('Arial', 15, 'bold'), command=lambda: controller.show_frame(ThirdPage))
            b1.place(x=27, y=290)

            b2 = Button(f2, text='Result for Application', width=25, bg='yellow', font=('Arial', 15, 'bold'), command=result)
            b2.place(x=27, y=290)

            b3 = Button(f3, text='Change Password', width=25, bg='yellow', font=('Arial', 15, 'bold'), command=changepass)
            b3.place(x=27, y=290)

            def togglemenu():

                def collapse():
                    toggle_menu.destroy()
                    toggle_btn.config(text='☰')
                    toggle_btn.config(command=togglemenu)

                toggle_menu = Frame(self, bg='orange')

                home_button=Button(toggle_menu, text='Home', font=('bold', 20),  bg='orange', fg='white', bd=0,  activebackground='orange', activeforeground='white', command=lambda: controller.show_frame(FirstPage))
                home_button.place(x=20, y=20)

                # def on_closing():
                #     if messagebox.askyesno(title='Quit?', message='Do you really want quit?'):
                #         self.destroy()

                logOut_button = Button(toggle_menu, text='Log Out', font=('bold', 20), bg='orange', fg='white', bd=0,
                                     activebackground='orange', activeforeground='white', command=exit)
                logOut_button.place(x=20, y=80)

                window_height = self.winfo_height()
                toggle_menu.place(x=1000, y=50, height=150, width=200)

                toggle_btn.config(text='X')
                toggle_btn.config(command=collapse)

            head_frame =Frame(self, bg='orange', highlightbackground='white', highlightthickness=1)

            title = Label(head_frame, text='Financial Assistance Application', bg='orange', fg='white', font=('bold', 20))
            title.pack(side=RIGHT)

            toggle_btn = Button(head_frame, text='☰', bg='orange', fg='white', font=('bold', 20), bd=0, activebackground='orange', activeforeground='white', command=togglemenu)
            toggle_btn.pack(side=RIGHT)

            head_frame.pack(side=TOP, fill=X)
            head_frame.pack_propagate(False)
            head_frame.configure(height=50)


        except Exception as e:
            print(f"Error loading images: {e}")

        self.label_username = Label(self, text="Username:", bg='white', font=('Arial', 16))
        self.label_username.pack(pady=5, anchor='nw')

        self.label_ic_number = Label(self, text="IC Number:", bg='white', font=('Arial', 16))
        self.label_ic_number.pack(pady=10, anchor='nw')
    def on_show(self, user_info=None):

        if user_info is not None:
            self.label_username.config(text=f"Username: {user_info.get('username', '')}")
            self.label_ic_number.config(text=f"IC Number: {user_info.get('ic_number', '')}")
        else:
            self.label_username.config(text="Username: ")
            self.label_ic_number.config(text="IC Number: ")


class FifthPage(Frame):

    def __init__(self, parent, controller):
        Frame.__init__(self, parent)

        self.config(bg='white')

        img = Image.open('registration.png')
        photo = ImageTk.PhotoImage(img)
        label = Label(self, image=photo)
        label.image=photo
        label.place(x=0, y=0)

        frame = Frame(self, width=950, height=400, bg='white')
        frame.place(x=125, y=70)

        label = Label(frame, text = 'Change Password', bg='white', font=('Arial', 30, 'bold'))
        label.place(x=360, y=30)

        l1 = Label(frame, text='IC Number', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l1.place(x=250, y=150)
        user = Entry(frame, width=25, bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        user.place(x=500, y=150)

        l2 = Label(frame, text='New Password', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l2.place(x=250, y=210)
        code = Entry(frame, width=25, fg='black', bd=3, show='*',bg='white', font=('Microsoft YaHei UI Light', 11))
        code.place(x=500, y=210)

        l3 = Label(frame, text='Confirm New Password', bg='white', font=('Microsoft YaHei UI Light', 11, 'bold'))
        l3.place(x=250, y=270)
        confirm = Entry(frame, width=25, fg='black', show='*', bd=3, bg='white', font=('Microsoft YaHei UI Light', 11))
        confirm.place(x=500, y=270)

        ##############################################-----------------------------------------------------------------------------

        def check():
            if user.get() != '' and code.get() != '' and confirm.get() != '':
                if code.get() == confirm.get():
                    with open('credential.txt', 'a') as f:
                        f.write(user.get() + ',' + code.get() + '\n')
                        messagebox.showinfo('Welcome', 'your password is changed successfully!!')
                    controller.show_frame(FourthPage)
                else:
                    messagebox.showinfo('Error', "Your password didn't get match!!")
            else:
                messagebox.showinfo('Error', "Please fill the complete field!!")

        Button(frame, width=39, pady=7, text='Change Password', bg='#57a1f8', fg='white', border=0, command=check).place(x=360,y=350)


class Application(Tk):
    def __init__(self, *args, **kwargs):
        Tk.__init__(self, *args, **kwargs)


        window = Frame(self)
        window.pack()

        window.grid_rowconfigure(0, minsize = 550)
        window.grid_columnconfigure(0, minsize=1200)

        self.frames = {}
        for F in (FirstPage, SecondPage, ThirdPage, FourthPage, FifthPage):
            frame = F(window, self)
            self.frames[F] = frame
            frame.grid(row = 0, column = 0, sticky='nsew')

        self.show_frame(FirstPage)

    def show_frame(self, page, *args, **kwargs):
        frame = self.frames[page]
        if hasattr(frame, 'on_show'):
            frame.on_show(*args, **kwargs)
        frame.tkraise()

app = Application()
app.maxsize(1200,550)
app.mainloop()

