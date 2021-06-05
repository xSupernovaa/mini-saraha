Bassel, 29 May

- created a new function in FilesManager, add_new_user_instance_to_disc(User new_user), it adds the new user creditials to disc, and creates a new folder for the user containing two files, sent_messages.txt and received_messages.txt

- next commit will contain: 
     loading all user instances from disc to the server
     
 ##Mario, 29 May
 - created registration function, function to validate password and function to check if the username is already exist or not
 - next commit: 
     login function


Ayman, 31 May
    • Finished server functions
    • Added cache variables for storage
    
Mario, 31 May
     -Finished Registration and login functions and their validations


Bassel, 01 Jun
    - created a new function in FilesManager, User load_user_instance_from_disc(int user_id), it returns a user instances with all its fields loaded from disc
    
 
Ayman, 2 Jun
    • Fixed bugs in server and menus where data wasn't propagated on server
    • Pushed new user into the users vector after registration

Ayman, 4 Jun commit 1
    • finished saveSession(), data now saves to disc
    • added undo last message logic

Ayman, 4 Jun commit 2
    • added save basic data to file
    • switched received messages to deque (better support for undo and display order)
    • fixed bugs in saveSession()
    • added favorite messages saving and deleting
    • userMenu now displays username not id
    • fixed messages display order (newer messages show at top now)
    • fixed bugs in messages holders (pops and pushes weren't targeting correct message)

    To Do:
        - view all the received messages from specific contact.
        - display sender id beside message content in view messages
        - view all contacts of specific user.
        - testing
        after the above is done: gui

Ayman, 5 Jun
    • added favorite messages gui
    • added base for received messages (couldn't figure out proper add to favorites method)