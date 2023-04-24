    //suv200000
    //Sohan Vidiyala

    //import libararies
    #include <iostream>
    #include <fstream>
    using namespace std;

    //define structure
    struct Node {

    //variable that holds # or * or nothing
    char data;
    //four pointers in each cardinal direction
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    //will be used to create + access/modify grid

    };

    //function prototypes
    Node* newRow(); //creates single row
    Node* restOfrows(); //creates 50x50 grid
    Node* drawUpDown(Node *, Node *, bool, char, int, bool, bool); //draws up or down
    bool validateUpDown(Node *, bool, char, int); //validates if up/down command is within bounds
    Node* drawLeftRight(Node *, Node *, bool, char, int, bool, bool); //draws left or right
    bool validateLeftRight(Node *, bool, char, int); //validates if left/right command is within bounds
    void printList(Node *, Node *, ostream &, int); //prints list
    void deleteList(Node *); //deletes list

    int main()
    {
    

    Node* initial; //will hold the initial position of the grid
    Node* curPos; // holds the current position of grid
    Node* firstPos; //will hold the very first position of grid

    //create grid
    Node* head = restOfrows(); //sets head at the start of the linked list grid
    //set all three pointers to head
    initial = head;
    curPos = head;
    firstPos = head;
        
    //get commands from file
        string filename;
        cout << "Enter file name: ";
        cin >> filename;
        
        //open input file
        ifstream inputFile;
        inputFile.open(filename.c_str(), ios::in | ios::binary);
        
        //open output file
        ofstream outputFile;
        outputFile.open("paint.txt");
        
        
        //variables that get passed to function
        bool pen = false;
        bool bold = false;
        bool print = false;
        int distance;
        char direction = '\0';
        
        //variables used to parse data from input file
        string command = "";
        string penStatus = "";
        string directionStatus = "";
        string distanceStatus = "";
        string boldStatus = "";
        string printStatus = "";
        long unsigned int comma = 0; //to get bold and print
        
        //while not at the end of file
        while (!inputFile.eof())
        {
            //while getting one line from the input file
            while (getline(inputFile, command))
            {
                //find a comma and store position
                comma = command.find(',');
                
                //reset variables
                bold = false;
                print = false;
                penStatus = "";
                directionStatus = "";
                distanceStatus = "";
                boldStatus = "";
                printStatus = "";
                
                //substring for pen status
                penStatus = command.substr(0, comma);
                
                if ((penStatus != "1") && (penStatus != "2"))
                {
                    continue;
                }
                
                //store penStatus value
                if (penStatus == "1")
                {
                    pen = false;
                }
                else if (penStatus == "2")
                {
                    pen = true;
                }
                
                //take off penStatus part from original string
                command = command.substr(comma + 1);
                comma = command.find(',');
                
                //substring for direction
                directionStatus = command.substr(0, comma);
                
                if ((directionStatus != "N") && (directionStatus != "S") && (directionStatus != "E") && (directionStatus != "W"))
                {
                    continue;
                }
                
                //input validation
                if ((directionStatus == "n") || (directionStatus == "s") || (directionStatus == "e") || (directionStatus == "w"))
                {
                    continue;
                }
                
                //set direction based off of command
                if ((directionStatus == "N") || (directionStatus == "S"))
                {
                    direction = directionStatus[0];
                }
                else if ((directionStatus == "E") || (directionStatus == "W"))
                {
                    direction = directionStatus[0];
                }
                
                //take off single command from string
                command = command.substr(comma + 1);
                //find comma
                comma = command.find(',');
                
                //substring for distance
                distanceStatus = command.substr(0, comma);
                
                //setting distance value
                distance = stoi(distanceStatus);
                
                if (distance < 1)
                {
                    continue;
                }
                
                //checks if there's still a comma
                //if there isn't, then already gotten entire command
                //if there is, still need to get B, P, or both
                if (command.find(',') != string::npos)
                {
                    //get index of comma
                    comma = command.find(',');
                    command = command.substr(comma + 1);
                    
                    //check again if there's a comma
                    //if there is then there's both B && P
                    //if not then only B || P
                    if (command.find(',') != string::npos)
                    {
                        //find comma position
                        comma = command.find(',');
                        //take off B and set to boldstatus
                        boldStatus = command.substr(0, comma);
                        //cut string down
                        command = command.substr(comma + 1);
                        //set rest of strinig to printStatus
                        printStatus = command;
                        
                        //input validation
                        if ((boldStatus != "B") && (printStatus != "P"))
                        {
                            continue;
                        }
                        
                        //input validation
                        if ((boldStatus == "b") || (printStatus == "p"))
                        {
                            continue;
                        }
                    }
                    else
                    {
                        //set boldstatus
                        if (command == "B")
                        {
                            boldStatus = command;
                        }
                        //set prinitstatus
                        else if (command == "P")
                        {
                            printStatus = command;
                        }
                        
                        //input validation
                        if ((command == "b") || (command == "p"))
                        {
                            continue;
                        }
                        
                        //input validation
                        if (command == "")
                        {
                            continue;
                        }
                        
                    }
                }
                
                //set bold
                if (boldStatus == "B")
                {
                bold = true;
                }
                
                //set print
                if (printStatus == "P")
                {
                print = true;
                }
                
                //if we want to move up/down
                if ((direction == 'N') || (direction == 'S'))
                {
                    //check command is within bounds
                    if (validateUpDown(curPos, pen, direction, distance) == false)
                    {
                        continue;
                    }
                    //if valid, move/draw up or down
                    curPos = drawUpDown(curPos, firstPos, pen, direction, distance, bold, print);
                }
                //if we want to move left/right
                else if ((direction == 'E') || (direction == 'W'))
                {
                    //check command is within bounds
                    if (validateLeftRight(curPos, pen, direction, distance) == false)
                    {
                        continue;
                    }
                    //if valid, move/draw left or right
                    curPos = drawLeftRight(curPos, firstPos, pen, direction, distance, bold, print);
                }
                
                //reset comma position
                comma = 0;
                //reset firstPos to the very first position
                firstPos = initial;
            }
            
            //if at the end of file, break out of loop
            if (inputFile.eof())
            {
                break;
            }
        }
        
    //print to file
    head = initial;
    int counter = 0;
    printList(head, firstPos, outputFile, counter);
        


    //delete grid
    head = initial;
    deleteList(head);
        
    //close files
    inputFile.close();
    outputFile.close();
    
    }

    Node* newRow()
    {
    //create a head and initial pointer
    Node* head = nullptr;
    Node* initial = nullptr;

    //loop that creates 50 nodes
    for(int i=0; i < 50; i++) {
        Node* newNode = new Node; // create a new node
        newNode->data = ' '; // set data to a space
        //set directional pointers to nullptr
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->up = nullptr;
        newNode->down = nullptr;
        
        //first row
        if (!head)
        {
            //attatch head to first node
            head = newNode;
            initial = head;
            //set left to nullptr
            newNode->left = nullptr;

        }
        else
        {
            //create traversal pointer
            Node* curr;
            curr = head;
            
            //traverse to the end of list
            while (curr->right != nullptr)
            {
                curr = curr->right;
            }

            //make the new node the very last and attatch the previous last node to the new node
            newNode->left = curr;
            newNode->right = curr->right;
            curr->right = newNode;
            
        }
    }

    //returns the very first position of linked list grid
    return initial;
    }

    Node* restOfrows()
    {
    //create a new row
    Node* prev_head = newRow();
    Node* tempHead = prev_head; //creates a temporary head set to the starting position of the newly created row
    
    //loop to create 49 more rows
    for(int i=1; i <= 49;i++) {
        //create a new row
        Node* curr_head = newRow();
        
        //temp node
        Node* temp = curr_head;
        
        //attatches the very first node up and down
        while (temp != nullptr){
            if (i == 0)
            {
                tempHead->up = nullptr;
                tempHead->down = temp;
                temp->up = tempHead;
            }
            else
            {
                //attatches the next nodes
                tempHead->down = temp;
                temp->up = tempHead;
            }
            
            //atatches the right links
            temp = temp->right;
            tempHead = tempHead->right;
        }
        
        //set the temporary head to the current head
        tempHead = curr_head;
    }
    
    //return position of very first linked list grid
    return prev_head;
    }

    /*
    void printList(Node *&head, ofstream &outputFile)
    {
        Node *initial = head;
        Node *rowHead = initial;
        int counter = 0;
        
        while(rowHead != nullptr)
        {
            while(initial != nullptr)
            {
                cout << initial->data;
                initial = initial->right;
                counter++;
            }
            
            cout << endl;
            rowHead = rowHead->down;
            initial = rowHead;
            cout << "\nFinal: " << counter << endl;
            counter = 0;
        }
        
    }
    */

    /*
    //iterative print
    void printList(Node *&head, ofstream &outputFile)
    {
    Node *initial = head;

    for (int i = 1; i <= 50; i++)
        {
        while (initial != nullptr)
        {
            cout << initial->data;
            outputFile << initial->data;
            initial = initial->right;
        }

        cout << endl;
        outputFile << endl;
    
        initial = head;
        for (int j = 0; j < i; j++)
            {
            initial = initial->down;
            }
        }
        
    }
    */
    

    //recursive print
    void printList(Node *head, Node * firstPos, ostream &outputFile, int counter)
    {
        //base case
        if (head == nullptr)
        {
            //increase counter
            counter++;
            
            //if not at the very last row
            if (counter != 50)
            {
                //then you can print a new line
                outputFile << endl;
            }
            
            //movce head back to the very first position
            head = firstPos;
            for (int j = 0; j < counter; j++)
            {
                //move head down to the row we want to print (based off of counter)
                head = head->down;
            }
            
            //if at the very bottom
            if (counter == 50)
            {
                //return everything, print
                return;
            }
        }
        
        //print data
        outputFile << head->data;
        //recursive call but with the next node in row
        printList(head->right, firstPos, outputFile, counter);
    }

    //deletes list
    void deleteList(Node *head)
    {
        //create an initial and set to head
        Node* initial = head;
        
        //loops through one row
        for (int i = 1; i <= 50; i++)
        {
            //until the very last node
            while (head != nullptr)
            {
                //delete each node
                head = head->right;
                delete head;
            }
            
            //set node back to initial
            head = initial;

            //moves down the row, specified by outer loop (i variable)
            for (int j = 0; j < i; j++)
            {
                head = head->down;
            }
        }
    }

    //draw up/down function
    Node* drawUpDown(Node *curPos, Node *firstPos, bool pen, char direction, int distance, bool bold, bool print)
    {
        //if only moving
        if (pen == false)
        {
            //if moving up
            if (direction == 'N')
            {
                //move up by number specified by distance
                for (int i = 1; i <= distance; i++)
                {
                    curPos = curPos->up;
                }
            }
            //if moving down
            else if (direction == 'S')
            {
                //move down by number specified by distance
                for (int i = 1; i <= distance; i++)
                {
                    curPos = curPos->down;
                }
            }
        }
        //if moving and drawing
        else if (pen == true)
        {
            //moving up
            if (direction == 'N')
            {
                //do distance number of times
                for (int i = 1; i <= distance; i++)
                {
                    //move up
                    curPos = curPos->up;
                    
                    //if B in command, draw #
                    if (bold == true)
                    {
                        curPos->data = '#';
                    }
                    else
                    {
                        //draw * if no B in command AND there isn't already a # in place
                        if (curPos->data != '#')
                        {
                            curPos->data = '*';
                        }
                    }
                }
            }
            //moving down
            else if (direction == 'S')
            {
                //do distance number of times
                for (int i = 1; i <= distance; i++)
                {
                    //movde down
                    curPos = curPos->down;
                    
                    //if B within command, draw #
                    if (bold == true)
                    {
                        curPos->data = '#';
                    }
                    else
                    {
                        //if no B, draw * if a # is not already in place
                        if (curPos->data != '#')
                        {
                            curPos->data = '*';
                        }
                    }
                }
            }
            
        }
        
        //if P wiithin command
        if (print == true)
        {
            //declare and initialize a counter to be used by recursive print function
            int counter = 0;
            //call print function
            printList(firstPos, firstPos, cout, counter);
            //print two buffer lines
            cout << endl << endl;
        }

        //return the current position
        return curPos;
    }

    //check if command is within bounds
    bool validateUpDown(Node *curPos, bool pen, char direction, int distance)
    {
        //create flag
        bool isValid = true;
        //store position of current position
        Node * current = curPos;
        
        //only moving, no drawing
        if (pen == false)
        {
            //moving up
            if (direction == 'N')
            {
                //do distance number of times
                for (int i = 1; i <= distance; i++)
                {
                    //if this position is nullptr
                    if (curPos->up == nullptr)
                    {
                        //command is invalid, stop loop
                        isValid = false;
                        break;
                    }
                    //moves up
                    curPos = curPos->up;
                }
            }
            //if moving down
            else if (direction == 'S')
            {
                for (int i = 1; i <= distance; i++)
                {
                    //if current position pointing down is nullptr
                    if (curPos->down == nullptr)
                    {
                        //set flag to false
                        isValid = false;
                        //break outta loop
                        break;
                    }
                    //move down
                    curPos = curPos->down;
                }
            }
        }
        
        //below code accomplishes same task, only difference is if pen is true
        else if (pen == true)
        {
            if (direction == 'N')
            {
                for (int i = 1; i <= distance; i++)
                {
                    if (curPos->up == nullptr)
                    {
                        isValid = false;
                        break;
                    }
                    curPos = curPos->up;
                }
            }
            else if (direction == 'S')
            {
                for (int i = 1; i <= distance; i++)
                {
                    if (curPos->down == nullptr)
                    {
                        isValid = false;
                        break;
                    }
                    curPos = curPos->down;
                }
            }
            
        }
        
        //set curPos to position it initially was when funcition called
        curPos = current;
        return isValid; //return if command is valid or invalid
    }

    //drwas left or right
    Node* drawLeftRight(Node *curPos, Node *firstPos, bool pen, char direction, int distance, bool bold, bool print)
    {
        //if only moving
        if (pen == false)
        {
            //if moving right
            if (direction == 'E')
            {
                //for distancew times
                for (int i = 1; i <= distance; i++)
                {
                    //move right
                    curPos = curPos->right;
                }
            }
            //if moving left
            else if (direction == 'W')
            {
                //for distance number of times
                for (int i = 1; i <= distance; i++)
                {
                    //move left
                    curPos = curPos->left;
                }
            }
        }
        //if moving + drawing
        else if (pen == true)
        {
            //if moving right
            if (direction == 'E')
            {
                //for distance times
                for (int i = 1; i <= distance; i++)
                {
                    //move right
                    curPos = curPos->right;
                    
                    //if B within command
                    if (bold == true)
                    {
                        //draw #
                        curPos->data = '#';
                    }
                    else
                    {
                        //if no B and no # already in place, draw *
                        if (curPos->data != '#')
                        {
                            curPos->data = '*';
                        }
                    }
                }
            }
            //draw left
            else if (direction == 'W')
            {
                //for distance times
                for (int i = 1; i <= distance; i++)
                {
                    //move left
                    curPos = curPos->left;
                    
                    //if B
                    if (bold == true)
                    {
                        //draw #
                        curPos->data = '#';
                    }
                    else
                    {
                        //if no B + no # already in place
                        if (curPos->data != '#')
                        {
                            //draw *
                            curPos->data = '*';
                        }
                    }
                }
            }
            
        }
        
        //if P
        if (print == true)
        {
            //declare + initialize counter to be used by print function
            int counter = 0;
            //call print function
            printList(firstPos, firstPos, cout, counter);
            //print two buffer lines
            cout << endl << endl;
        }

        //returns current position
        return curPos;
    }

    //checks if left/right command is within bounds
    bool validateLeftRight(Node *curPos, bool pen, char direction, int distance)
    {
        //create flag and set to true
        bool isValid = true;
        //store position of current position
        Node *current = curPos;
        
        //if not drawing
        if (pen == false)
        {
            //moving east
            if (direction == 'E')
            {
                //for distance times
                for (int i = 1; i <= distance; i++)
                {
                    //position to the right is nullptr, set flag to false + break outta loop
                    if (curPos->right == nullptr)
                    {
                        isValid = false;
                        break;
                    }
                    //move right
                    curPos = curPos->right;
                }
            }
            //if moving left
            else if (direction == 'W')
            {
                //for distance number of times
                for (int i = 1; i <= distance; i++)
                {
                    //if value to left is nullptr, set flag to false + break outta loop
                    if (curPos->left == nullptr)
                    {
                        isValid = false;
                        break;
                    }
                    //move left
                    curPos = curPos->left;
                }
            }
        }
        //below code accomplishes same thing, just also if command is moving + drawing
        else if (pen == true)
        {
            if (direction == 'E')
            {
                for (int i = 1; i <= distance; i++)
                {
                    if (curPos->right == nullptr)
                    {
                        isValid = false;
                        break;
                    }
                    curPos = curPos->right;
                }
            }
            else if (direction == 'W')
            {
                for (int i = 1; i <= distance; i++)
                {
                    if (curPos->left == nullptr)
                    {
                        isValid = false;
                        break;
                    }
                    curPos = curPos->left;
                }
            }
            
        }
        
        //set current position back to where it initially was when function called
        curPos = current;
        //returns whether command is valid or invalid
        return isValid;
    }

