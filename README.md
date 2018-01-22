# Temporal Logic Primitive for C++ 

[Temporal logic](https://en.wikipedia.org/wiki/Temporal_logic) is a fascinating space. It talks about not just our traditional Boolean (true / false) expressions, but at what point in time a value is likely to be true or false. It can allow us as developers to write things like `when (condition is true) then do (function)`. We can even write statements which state that a condition isn’t true now, but will in the future. This can sound a little confusing at first. But temporal logic can get really interesting, and very useful when you consider that a lot of todays’ development is event driven, and since events always occur at given point in time, they are by definition temporal. These events can be web requests / restfulAPI invocations, or user input. The tools and mind-set that temporal logic provides can allow us to solve what seem like initially complex problems with rather simple code.

 

## Detecting a Shake

I wanted to write a simple Windows application called [Waggle My Mouse](https://gumroad.com/products/zCMp), that would detect when the mouse was shaken fast side by side. This shake or “waggle” is then used to highlight the mouse cursor, allowing the user to quickly locate it. Working on multi monitor or high resolution 4k windows workstations had been driving me nuts, I kept losing my mouse pointer and didn’t know which screen to look at when searching for it.

After a lot of research ([details on my personal blog](http://withbighair.com/continuing-to-waggle-my-mouse/)), I discovered that the best way to detect the waggle was to detect when the velocity of the x-axis of the mouse exceeded a given threshold. This told me the user had dramatically moved the mouse across the screen on the x-axis, a shake or waggle, would consist of 5 or more of these movements within a given time window.

The statement I needed to write was:

​     *(the mouse’s x-axis velocity exceeds the threshold 5 times in one second) Then highlight the mouse*

 

## Introducing the TBool

I did a lot of thinking about how to spot the shake ([discussed on my personal blog](http://withbighair.com/detecting-a-waggle/)), I determined that I needed to create a temporal "bit" (as I referred to it originally), a Boolean value which I could set to true, and would decay over time. This maps directly to the temporal logic concept that a value is only ever true for a given period of time. This became the temporal logic primitive, TBool.

The TBool is a simple C++ implementation of temporal Boolean. Just like a normal Boolean this is a value that is set to be true based on a conditional statement. However unlike a normal Boolean, the “truth”of this value only lasts for the specified “lifetime” of the TBool before the TBool reverts to its false state. 

![A normal bool is set true, and stays true](readme_images/normalbool.png?raw=true)

We can set the TBool to true “now” and it will remain true for a given period of time, after which the value will be false.

![A temporal Boolean value decays over time](readme_images/temporalbool.png?raw=true)

It is possible to have the TBool continue to stay true for a longer period of time. We can do this by continually refreshing the value of the TBool, setting it true repeatedly. Doing this resets the TBool’s life timer, preserving the value within it for longer.

![A temporal Boolean can be reset repeatedly to preserve state](readme_images/temporalboolreset.png?raw=true) 

Using the TBool to solve the Shake Statement then becomes rather straight forward. Listening to the Window event queue we can get information on the x-axis accelerator from the mouse. Once the threshold is crossed the value is stored in an array of 5 TBools. Each TBool has a “life” of 1 second.

```c++
const size_t MAX_SHAKES = 5; 
TBool thresholdCrossed[MAX_SHAKES];
size_t index = 0;
….
thresholdCrossed [index] = true;
index = (index + 1) % MAX_SHAKES;
```
It is then possible to easily check if 5 shakes have been detected in the 1 second window. This is done by simply evaluating the contents of the array.

```c++
bool shakeDetected() {
  bool shakeFound= true;
  for (size_t i = 0; (i < MAX_SHAKES && shake_found); i++) {
    shakeFound= thresholdCrossed[i]; 
  }
  return shakeFound;
}
```

In the Waggle My Mouse application this check is performed as part of the mouse event handling code.

## TBool Example Application

Temporal logic and TBools can help us as developers more easily write code to respond to what initially appear to be complex states. An example implementation of a TBool is provided under the Apache 2 License on GitHub. The originally application which inspired the creation of the TBool, “[Waggle My Mouse](https://gumroad.com/products/zCMp)” a mouse cursor location tool for Windows, is available to purchase via [GumRoad](https://gumroad.com/products/zCMp). Anyone who would like to provide me with feedback on Waggle My Mouse can get a free copy by contacting me on Twitter [@mcwoods](https://twitter.com/mcwoods).

## Using TBool

If you'd like to use the TBool in your own projects please feel free to do so. The GitHub repository contains the TBool header file, which is all you need to include in your project to use it. There is also a small demonstration command line program which illustrates the TBool's temporal nature.

There are many possible uses for this type of temporal logic:

* Simple monitoring of an application's SLA
* Deterministic programming; not just computing a value, but where the quality of the result is time bound
* Simple ways to implement CEP ([complex event processing](https://en.wikipedia.org/wiki/Complex_event_processing)) like functionality without needing a full blow CEP Engine
* Implementation of low pass filters (as illustrated by Waggle My Mouse)

## Looking into the Future

There are many more temporal logic primitives and constructs that can be implemented in C++. This could allow more complicated temporal statements which would allow the temporal nature of TBools to be combined to define future logical outcomes, for instance:

​     *when x is true for 5 seconds and z is false for 3 seconds then when x becomes false y should be set to true*



...but that is going to require a bit more thinking...