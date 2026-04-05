#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

// Structure
struct Staff {
    int id;
    char name[50];
    char role[30];
    struct Staff* child;
    struct Staff* sibling;
};

struct Staff* root = NULL;

// Create node
struct Staff* createNode(int id, char name[], char role[]) {
    struct Staff* newNode = (struct Staff*)malloc(sizeof(struct Staff));
    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->role, role);
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Search
struct Staff* search(struct Staff* root, int id) {
    if (!root) return NULL;
    if (root->id == id) return root;

    struct Staff* found = search(root->child, id);
    if (found) return found;

    return search(root->sibling, id);
}

// Check duplicate ID
int idExists(struct Staff* root, int id) {
    return search(root, id) != NULL;
}

//  ROLE MENU
void chooseRole(char role[]) {
    int choice;

    printf("\nSelect Role:\n");
    printf("1. VC\n");
    printf("2. DEAN\n");
    printf("3. HOD\n");
    printf("4. PROFESSOR\n");
    printf("5. ASSISTANT PROFESSOR\n");
    printf("6. LECTURER\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: strcpy(role, "VC"); break;
        case 2: strcpy(role, "DEAN"); break;
        case 3: strcpy(role, "HOD"); break;
        case 4: strcpy(role, "PROFESSOR"); break;
        case 5: strcpy(role, "ASSISTANT PROFESSOR"); break;
        case 6: strcpy(role, "LECTURER"); break;
        default:
            printf("Invalid role!\n");
            role[0] = '\0';
    }
}

// Hierarchy validation
int validHierarchy(char parent[], char child[]) {
    if (strcmp(parent,"VC")==0 && strcmp(child,"DEAN")==0) return 1;
    if (strcmp(parent,"DEAN")==0 && strcmp(child,"HOD")==0) return 1;
    if (strcmp(parent,"HOD")==0 && strcmp(child,"PROFESSOR")==0) return 1;
    if (strcmp(parent,"PROFESSOR")==0 && strcmp(child,"ASSISTANT PROFESSOR")==0) return 1;
    if (strcmp(parent,"ASSISTANT PROFESSOR")==0 && strcmp(child,"LECTURER")==0) return 1;
    return 0;
}

// Add Staff
void addStaff() {
    int id, parentId;
    char name[50], role[30];

    printf("Enter ID: ");
    scanf("%d", &id);
    getchar();

    if (idExists(root, id)) {
        printf("ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name,"\n")] = '\0';

    //  ROLE SELECTION
    chooseRole(role);
    if (role[0] == '\0') return;

    struct Staff* newNode = createNode(id, name, role);

    // Root creation
    if (root == NULL) {
        if (strcmp(role, "VC") != 0) {
            printf("First node must be VC!\n");
            free(newNode);
            return;
        }
        root = newNode;
        printf("VC created as root!\n");
        return;
    }

    printf("Enter Parent ID: ");
    scanf("%d", &parentId);

    struct Staff* parent = search(root, parentId);

    if (!parent) {
        printf("Parent not found!\n");
        free(newNode);
        return;
    }

    if (!validHierarchy(parent->role, role)) {
        printf("Invalid hierarchy relation!\n");
        free(newNode);
        return;
    }

    // Insert child
    if (!parent->child)
        parent->child = newNode;
    else {
        struct Staff* temp = parent->child;
        while (temp->sibling)
            temp = temp->sibling;
        temp->sibling = newNode;
    }

    printf("Staff added successfully!\n");
}

//  DISPLAY TREE
void displayTree(struct Staff* root, int level, int isLast, int indent[]) {
    if (!root) return;

    for (int i = 0; i < level; i++) {
        if (indent[i] == 1)
            printf("|   ");
        else
            printf("    ");
    }

    if (level > 0) {
        if (isLast)
            printf("\\-- ");
        else
            printf("|-- ");
    }

    printf("%d - %s (%s)\n", root->id, root->name, root->role);

    struct Staff* temp = root->child;
    int count = 0;
    while (temp) {
        count++;
        temp = temp->sibling;
    }

    temp = root->child;
    int i = 0;

    while (temp) {
        indent[level] = (i != count - 1);
        displayTree(temp, level + 1, (i == count - 1), indent);
        temp = temp->sibling;
        i++;
    }
}

// Update
void updateStaff() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    getchar();

    struct Staff* node = search(root, id);

    if (!node) {
        printf("Not found!\n");
        return;
    }

    printf("Enter new name: ");
    fgets(node->name, sizeof(node->name), stdin);
    node->name[strcspn(node->name,"\n")] = '\0';

    printf("Updated successfully!\n");
}

// Delete (leaf only)
int deleteNode(struct Staff* parent, struct Staff* node, int id) {
    if (!node) return 0;

    if (node->id == id) {
        if (node->child) {
            printf("Deletion not allowed: Staff has subordinates!\n");
            return 1;
        }

        if (parent->child == node)
            parent->child = node->sibling;
        else {
            struct Staff* temp = parent->child;
            while (temp->sibling != node)
                temp = temp->sibling;
            temp->sibling = node->sibling;
        }

        free(node);
        printf("Deleted successfully!\n");
        return 1;
    }

    if (deleteNode(node, node->child, id)) return 1;
    return deleteNode(parent, node->sibling, id);
}

void deleteStaff() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    if (!root) {
        printf("Tree empty!\n");
        return;
    }

    if (root->id == id) {
        if (root->child) {
            printf("Cannot delete root with subordinates!\n");
            return;
        }
        free(root);
        root = NULL;
        printf("Root deleted!\n");
        return;
    }

    if (!deleteNode(root, root->child, id))
        printf("Not found!\n");
}

// Count roles
void countRoles(struct Staff* root, int count[]) {
    if (!root) return;

    if (strcmp(root->role,"VC")==0) count[0]++;
    else if (strcmp(root->role,"DEAN")==0) count[1]++;
    else if (strcmp(root->role,"HOD")==0) count[2]++;
    else if (strcmp(root->role,"PROFESSOR")==0) count[3]++;
    else if (strcmp(root->role,"ASSISTANT PROFESSOR")==0) count[4]++;
    else if (strcmp(root->role,"LECTURER")==0) count[5]++;

    countRoles(root->child, count);
    countRoles(root->sibling, count);
}

void showCount() {
    int count[6] = {0};
    countRoles(root, count);

    printf("\nVC: %d\nDean: %d\nHOD: %d\nProfessor: %d\nAssistant Professor: %d\nLecturer: %d\n",
           count[0], count[1], count[2], count[3], count[4], count[5]);
}

// Main
int main() {
    int choice;

    while (1) {
        printf("\n===== UNIVERSITY ADMIN HIERARCHY SYSTEM =====\n");
        printf("1. Add Staff\n");
        printf("2. Display Hierarchy\n");
        printf("3. Update Staff\n");
        printf("4. Delete Staff\n");
        printf("5. Search Staff\n");
        printf("6. Count Staff by Role\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStaff(); break;

            case 2: {
                int indent[100] = {0};
                displayTree(root, 0, 1, indent);
                break;
            }

            case 3: updateStaff(); break;
            case 4: deleteStaff(); break;

            case 5: {
                int id;
                printf("Enter ID: ");
                scanf("%d", &id);
                struct Staff* res = search(root, id);
                if (res)
                    printf("Found: %s (%s)\n", res->name, res->role);
                else
                    printf("Not found!\n");
                break;
            }

            case 6: showCount(); break;
            case 7: exit(0);

            default: printf("Invalid choice!\n");
        }
    }
}
