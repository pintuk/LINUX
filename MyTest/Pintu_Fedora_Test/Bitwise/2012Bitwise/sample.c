  #include <stdio.h> 

  int main()
  {
  int testcases, a, b, diff, sum;

  // Read the number of testcases
  scanf("%d",&testcases);

  while(testcases!=0)
  {
    // Read the two integers
    scanf("%d %d",&a,&b);
    //scanf("%d",&b);

    sum = a + b;
    diff = a - b;

    // Output the sum & difference
    printf("%d %d\n",sum,diff);
    testcases--;
  }

  return 0;
  } 

