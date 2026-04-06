→TITLE

Administration Hierarchy System

→TEAM MEMBERS

P. Lakshmi Prasanna

S. Arsheen

→PROBLEM STATEMENT

This project implements a University Administration Hierarchy System using a Tree Data Structure in C.

It models a real-life university structure such as:

VC → Dean → HOD → Professor → Assistant Professor → Lecturer

The system supports CRUD operations including:

Adding staff

Updating staff details

Deleting staff (with constraints)

Searching staff

Displaying hierarchy in tree format

Counting staff by roles

The program is menu-driven and demonstrates hierarchical relationships using pointers.

→DATA STRUCTURE USED

General Tree (Child-Sibling Representation)

Each node contains:

ID → Unique identifier

Name → Staff name

Role → Position (VC / Dean / HOD / etc.)

child → Pointer to first subordinate

sibling → Pointer to next staff at same level

→ALGORITHM EXPLANATION

1. Function: createNode()

Steps:

Allocate memory using malloc

Assign ID, name, and role

Set child = NULL

Set sibling = NULL

Return the new node

2. Function: search(root, id)

Steps:

If root is NULL → return NULL

If ID matches → return node

Recursively search:

First in child

Then in sibling

Return result

3. Function: addStaff()

Steps:

Input ID and name

Check duplicate ID

Select role using menu

Create new node

Root Condition:

If tree is empty:

Only VC can be root

For other nodes:

Input parent ID

Search parent node

Validate hierarchy:

VC → Dean

Dean → HOD

HOD → Professor

Professor → Assistant Professor

Assistant Professor → Lecturer

Insert node:

If no child → attach directly

Else → insert at end of sibling list

4. Function: validHierarchy(parent, child)

Steps:

Check valid role relationship

Return 1 if valid

Else return 0

5. Function: displayTree(root, level)

Steps:

If root is NULL → return

Print indentation based on level

Print node (ID, Name, Role)

Recursively:

Display child (level + 1)

Display sibling (same level)

Displays hierarchy in tree format

6. Function: updateStaff()

Steps:

Input ID

Search node

If found:


Input new name

Update value

Else print error

7. Function: deleteStaff()

Steps:

Input ID

Check if tree is empty

Root Deletion:

Allowed only if no children

Other Nodes:

Call deleteNode()

8. Function: deleteNode(parent, node, id)

Steps:

Traverse tree recursively

If ID matches:

Check if node has children

If YES → deny deletion

If NO:

Adjust sibling pointer

Remove node

Free memory

Continue recursion

Only leaf node deletion is allowed

9. Function: countRoles()

Steps:

Traverse entire tree

Count each role:

VC

Dean

HOD

Professor

Assistant Professor

Lecturer

10. Function: showCount()

Steps:

Call countRoles()

Display total count of each role

11. Function: Main Menu

Steps:

Display menu options:

1. Add Staff

2. Display Hierarchy

3. Update Staff

4. Delete Staff

5. Search Staff

6. Count Staff by Role

7. Exit

Take user input

Call respective function

Repeat until exit

IMPORTANT DESIGN DECISION

Deletion Rule:

Only leaf nodes can be deleted

Reason:

Prevents breaking hierarchy

Avoids loss of subordinate data

Keeps tree structure safe

→COMPILATION INSTRUCTIONS

Using VS Code:

Install C/C++ extension

Install MinGW / GCC compiler

Open project folder

Compile:

Bash

gcc yourfile.c -o output

Run:

Bash

./output

→SCREENSHOTS:

1. Adding Staff

<img width="488" height="461" alt="image" src="https://github.com/user-attachments/assets/4a5f68fd-1522-45f7-9252-f24443643132" />

*

<img width="474" height="487" alt="image" src="https://github.com/user-attachments/assets/7a6276b8-03f6-4036-b642-67dad135e703" />

*

<img width="514" height="496" alt="image" src="https://github.com/user-attachments/assets/68048d80-a780-4d8f-ae85-8f63aa421722" />

*  

<img width="486" height="492" alt="image" src="https://github.com/user-attachments/assets/6a85a5b0-7bb9-496d-9758-52317d63d186" />

2. Deletion

<img width="461" height="259" alt="image" src="https://github.com/user-attachments/assets/72553bf2-6f76-4739-9e34-33969b457fb6" />

*

<img width="468" height="251" alt="image" src="https://github.com/user-attachments/assets/3b32ab2d-5d29-44b7-9cfc-749cc9431db0" />

3. Update

<img width="471" height="279" alt="image" src="https://github.com/user-attachments/assets/0b649f89-9484-416e-9576-35d491cb4e00" />

4. Search

<img width="449" height="251" alt="image" src="https://github.com/user-attachments/assets/14b9bc41-002e-4436-a1c5-73841849be54" />

5. Count by Role

<img width="457" height="359" alt="image" src="https://github.com/user-attachments/assets/2ab437c8-8395-4834-a5f6-e3f5e3a82370" />

6. Display

<img width="445" height="302" alt="image" src="https://github.com/user-attachments/assets/6c89c8df-6dd0-4500-91e2-801c949ea5f1" />
