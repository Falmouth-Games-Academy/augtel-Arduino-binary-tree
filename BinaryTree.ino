
struct node *search(char key, struct node *leaf)
{
  if( leaf != 0 )
  {
      if(key==leaf->key_value)
      {
          return leaf;
      }
      else if(key<leaf->key_value)
      {
          return search(key, leaf->left);
      }
      else
      {
          return search(key, leaf->right);
      }
  }
  else return 0;
}

struct node traverse(char p[], struct node *leaf){
  if (leaf != 0){

    int l = strlen(p);

    struct node *currentNode = leaf;

    for (int i = 0; i < l; i++){

      if (p[i] == 'l') {
        currentNode = currentNode->left;
      }else if (p[i] == 'r'){
        currentNode = currentNode->right;
      }
      
    }

    return *currentNode;
    
  }
}


struct node *get(int i, struct node *leaf)
{
  if( leaf != 0 )
  {
      if(i==leaf->index)
      {
          return leaf;
      }
      else if(i < leaf->index)
      {
          return search(i, leaf->left);
      }
      else
      {
          return search(i, leaf->right);
      }
  }
  else return 0;
}




void insert(char key, int index,  struct node **leaf, char dir = '-')
{
    if( *leaf == 0 )
    {
        if (debug){
          Serial.print(dir);
          Serial.print(" load: ");
          Serial.print(index);
          Serial.print(" - ");
          Serial.println(key);
        }
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->key_value = key;
        (*leaf)->index = index;
        /* initialize the children to null */
        (*leaf)->left = 0;    
        (*leaf)->right = 0;  
    }
    else if(index < (*leaf)->index)
    {
        if (debug) Serial.println("Step left");
        insert( key, index, &(*leaf)->left, 'L' );
    }
    else if(index > (*leaf)->index)
    {
        if (debug) Serial.println("Step Right");
        insert( key, index, &(*leaf)->right, 'R' );
    }
}
