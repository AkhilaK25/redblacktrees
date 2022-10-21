#include <iostream>
using namespace std;

struct node
{

  int age;
  // colour should be either red='r' or black='b'
  char colour;
  struct node *left;
  struct node *right;
  struct node *parent;
};
struct node *root, *rp;

// Function for right rotation of the nodes
struct node *rotateright(struct node *pp)
{
  struct node *ap;
  ap = pp->left;
  pp->left = ap->right;
  if (ap->right != rp)
  {
    ap->right->parent = pp;
  }
  ap->parent = pp->parent;
  if (pp->parent == rp)
  {
    root = ap;
  }
  else if (pp == pp->parent->right)
  {
    pp->parent->right = ap;
  }
  else
  {
    pp->parent->left = ap;
  }
  ap->right = pp;
  pp->parent = ap;
  return pp;
}

// Function for left rotation of the nodes
struct node *rotateleft(struct node *pp)
{
  struct node *ap;
  ap = pp->right;
  pp->right = ap->left;
  if (ap->left != rp)
  {
    ap->left->parent = pp;
  }
  ap->parent = pp->parent;
  if (pp->parent == rp)
  {
    root = ap;
  }
  else if (pp == pp->parent->left)
  {
    pp->parent->left = ap;
  }
  else
  {
    pp->parent->right = ap;
  }
  ap->left = pp;
  pp->parent = ap;
  return pp;
}

struct node *insert2(struct node *root, struct node *ptr)
{

  struct node *uncle;
  struct node *par;
  struct node *grapar;

  if (ptr->parent != NULL && ptr->parent->colour == 'r')
  {
    if (ptr->parent->parent != NULL)
    {
      par = ptr->parent;
      grapar = par->parent;

      if (par == grapar->left)
      {
        uncle = grapar->right;
        // if uncle is red
        // recolouring the nodes
        if (uncle->colour == 'r' && uncle != NULL)
        {
          par->colour == 'b';
          uncle->colour = 'b';
          grapar->colour = 'r';
          root = insert2(root, grapar);
        }
        // if uncle is black
        // rotating the nodes and then recolouring
        else
        {
          if (ptr = par->right)
          {

            ptr = par;
            ptr = rotateleft(ptr);
            root = insert2(root, ptr);
          }
          else
          {
            par->colour = 'b';
            grapar->colour = 'r';
            grapar = rotateright(grapar);
          }
        }
      }
      else
      {
        if (par == grapar->right)
        {
          uncle = grapar->left;
          // if uncle is red
          // recolouring the nodes
          if (uncle->colour == 'r' && uncle != NULL)
          {
            par->colour = 'b';
            uncle->colour = 'b';
            grapar->colour = 'r';
            root = insert2(root, grapar);
          }
          else
          {
            // if uncle is black
            // rotating the nodes and then recolouring
            if (ptr == par->left)
            {
              ptr = par;
              ptr = rotateright(ptr);
              root = insert2(root, ptr);
            }
            else
            {

              par->colour = 'b';
              grapar->colour = 'r';
              grapar->right = par->left;

              if (par->left != NULL)
              {
                ptr->parent->left->parent = ptr->parent->parent;
              }
              if (ptr->parent->parent->parent != NULL)
              {
                if (ptr->parent->parent->parent->left == ptr->parent->parent)
                {
                  ptr->parent->parent->parent->left = ptr->parent;
                }

                else
                {
                  ptr->parent->parent->parent->right = ptr->parent;
                }
              }

              ptr->parent->left = ptr->parent->parent;
              ptr->parent->parent = ptr->parent->parent->parent;
              ptr->parent->left->parent = ptr->parent;
              root = ptr->parent;
            }
          }
        }
      }
    }
  }
  if (root->parent == rp)
    root->colour = 'b';
  else
  {
    while (root->parent != rp)
    {
      root = root->parent;
    }
    root->colour = 'b';
  }
  return root;
}

// Function for insertion of age of faculty
struct node *insert(int age)
{

  struct node *ptr, *par;
  par = rp;
  ptr = root;
  cout << "Enter the faculty age:\n";
  cin >> age;
  cout << "\n";

  struct node *newNode;
  newNode = (struct node *)malloc(sizeof(struct node));

  newNode->age = age;
  newNode->left = rp;
  newNode->right = rp;
  newNode->parent = rp;
  newNode->colour = 'r';

  while (ptr != rp)
  {
    par = ptr;
    if (age <= ptr->age)
    {
      ptr = ptr->left;
    }
    else if (age > ptr->age)
    {
      ptr = ptr->right;
    }
  }

  if (par == rp)
  {
    root = newNode;
  }
  else if (newNode->age <= par->age)
  {
    par->left = newNode;
    newNode->parent = par;
  }
  else
  {
    par->right = newNode;
    newNode->parent = par;
  }

  return insert2(root, newNode);
}

// Function to search the age of the faculty
struct node *search(struct node *ptr, int age)
{

  cout << "Enter the faculty age to be searched ";
  cin >> age;

  if (root == NULL)
  {
    cout << "Tree is empty\n\n";
    return NULL;
  }
  else
  {

    if (age < ptr->age)
    {
      ptr = ptr->left;
    }
    else if (age > ptr->age)
    {
      ptr = ptr->right;
    }
    else
    {
      cout << "Faculty with age " << age << " is found in the list.\n\n";
      return ptr;
    }
  }
  cout << "Faculty with age " << age << " is not found in the list\n\n";
  return NULL;
}

void print(struct node *ptr)
{
  if (ptr != rp)
  {
    if (ptr->left != NULL)
      print(ptr->left);
    cout << "Tree is " << ptr->age;
    if (ptr->right != NULL)
      print(ptr->right);
  }
}

int main()
{

  int age;
  int choice;
  struct node *root = NULL;
  struct node *ptr;

  rp = (struct node *)malloc(sizeof(struct node));

  rp->age = 0;
  rp->colour = 'b';
  root = rp;

  do
  {

    cout << "1 is to insert the age of faculty\n2 is to search \n3 is for inorder traversal\n";
    cout << "Enter the choice ";
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      root = insert(age);
      break;

    case 2:
      ptr = search(root, age);
      break;

    case 3:
      print(root);
      break;

    default:
      cout << "Enter valid choice\n\n";
    }
  } while (choice != 'r');

  return 'r';
}