#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include "rover.h"

#include <stdio.h>  // for printf

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/

void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   //CU_ASSERT(CU_FALSE);
   CU_ASSERT_NOT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string a#1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
}

void speed_test(void){
   output_controller output;
   output.freq_echantillonage=1;
   output.retour_base=false;

   rover rover_robot=create_rover(0,0,100);
   CU_ASSERT(speed_max_control(rover_robot));
   
}

void button_emergency_test(void){
   output_controller output;
   output.freq_echantillonage=6;
   output.retour_base=false;

   rover rover_robot=create_rover(0,0,100);
   CU_ASSERT(!(rover_robot.button_emergency));
   button_pressed(&rover_robot);
   CU_ASSERT(rover_robot.button_emergency);
}

/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "rover_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "speed_test", speed_test))||
        (NULL == CU_add_test(pSuite, "button_emergency_test", button_emergency_test))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }
/*
   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
*/
   // Run all tests using the automated interface
   CU_automated_run_tests();
//   CU_list_tests_to_file();

   // Run all tests using the console interface
  // CU_console_run_tests();

   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
