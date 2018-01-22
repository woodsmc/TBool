/******************************************************************************
* TBool - An example Temporal Boolean Primative                               *
*                                                                             *
* Copyright Notice and License                                                *
*  (c) Copyright 2018 Chris Woods.                                            *
*                                                                             *
*  Licensed under the Apache License, Version 2.0 (the "License"); you may    *
*  not use this file except in compliance with the License. You may obtain a  *
*  copy of the License at :  [http://www.apache.org/licenses/LICENSE-2.0]     *
*                                                                             *
*  Unless required by applicable law or agreed to in writing, software        *
*  distributed under the License is distributed on an "AS IS" BASIS,          *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
*  See the License for the specific language governing permissions and        *
*  limitations under the License.                                             *
*                                                                             *
******************************************************************************/


#include "tbool.h"
#include <iostream>
#include <string>
#include <thread>



void printMessage(const std::string& message) {
	std::time_t t = std::chrono::system_clock::to_time_t(  std::chrono::system_clock::now() );
	char time[100];
	std::strftime(time, sizeof(time), "%T", std::localtime(&t));
	std::cout << time << " | " << message << std::endl;
}


int main(int argc, const char* argv[]) {
	//auto a = DEFAULT_TIME_TRUE_MILLISECONDS;
	printMessage( "A jolly temporal hello world to you all" );
	printMessage( "First let's create a TBool, called bit and set it true, then wait for it to expire" );
	TBool bit;
	bit = true;
	while( bit ) { // should take about 0.5 seconds
		std::this_thread::sleep_for( std::chrono::milliseconds(100) );
	} 
	printMessage( "The TBool is now false\n\n" );

	

	printMessage( "Now, let's create a TBool which has a 5 second life." );
	TBool five_secs( std::chrono::milliseconds(5000) );
	printMessage( "When first created all TBools are false, so waiting will be fast, as value is false");	
	while( true == five_secs ) {} // super fast pass through
	printMessage( "The TBool is now false" );
	printMessage( "That fast fast huh!\n\n" );

	printMessage( "Now let's set that value to true, and wait..." );
	five_secs = true;
	while( five_secs ) { // should take about 5 seconds
		std::this_thread::sleep_for( std::chrono::milliseconds(100) );
	} 
	printMessage( "The TBool is now false" );
	printMessage( "That should have taken about 5 seconds" );

	return 0;
}