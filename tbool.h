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


#ifndef TBool_H_
#define TBool_H_

#include <chrono>
#include <ctime>

class TBool {	
	static constexpr size_t DEFAULT_TIME_TRUE_MILLISECONDS = 500;

	public:
		TBool() noexcept {
			setLife(std::chrono::milliseconds(size_t(DEFAULT_TIME_TRUE_MILLISECONDS)));
			setFalse();			
		}

		explicit TBool(std::chrono::milliseconds life) noexcept {
			setLife(life);
			setFalse();
		}
	
		bool operator=(bool right) noexcept {
			if (right)
				setTrue();
			else
				setFalse();
			return right;
		}
		
		explicit operator bool() const noexcept {
			return isTrue();
		}
		
		void setTrue() noexcept {
			time_set = std::chrono::steady_clock::now();
		}

		void setFalse() noexcept {
			time_set = std::chrono::steady_clock::now() - life;
		}

		bool isTrue() const noexcept {
			return (time_set + life) > std::chrono::steady_clock::now();
		}

		std::chrono::milliseconds getLife() const noexcept { 
			return life;
		}

		void setLife(std::chrono::milliseconds life) noexcept {
			this->life = life;
		}

	private:		
		std::chrono::time_point<std::chrono::steady_clock>	time_set;
		std::chrono::milliseconds 							life;
};


inline bool operator==(bool right, TBool left) {
	return left.isTrue() == right;
}

inline bool operator==(TBool right, bool left) {
	return right.isTrue() == left;
}


#endif // TBool_H_


