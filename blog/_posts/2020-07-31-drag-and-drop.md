---
layout: post
title: "Drag and drop project"
date: 2020-07-31
author: Raheem Clemons
---
Description: I am working to eventually implement a better drag and drop feauture to Avida-ed 4 that works on touch screen devices and can be used in classrooms. This feature will allow users to drag objects from the freezer and use it to populate the canvas, it will also allow movement on the canvas, movment to resources and movment of objects to trash.

## Objectives
* #### To find .js Library that enables drag and drop features on touch devices
* #### Build sample web app to be run on any touchscreen device
* #### use web app to demonstrate how it can meet all desired requirements for Avida-ed 4
----


Find Library
--
This involved looking at several JavaScript libraries and determining which ones would best serve my purposes
|Libraries |Descriprion|
|---|---|
|BootStrap | The current library that Avida-ed 4 heavily relies on. while it has good uses as a framework and in setting up the Avida-ed's layout it has no drag and drop features that were made for mobile or touchscreen devices|
|Dragula   | I chose tho use this library for a couple of reasons, it is :Dependency-free, works with touch devices, uses DOM elements for drag and drop, customizable settings that allowed drag and drop functions to work differently when being taken and/or dropped from different contianers. |
|Sortable  |Another Javascript library that allows for drag and drop features with mobile/touchscreen devices. Better with animations and styling (Bootstap compatable) however I chose Dragula because it had better information in manipulating DOM and dropping into divs|


After choosing Dragula as the main library I would use to implement drag and drop features I worked in code pin and began creating a mock Avida-ed 4 webpage. I also used JQuerey to help with DOM manipulation/selection.

Implementing Features
--
### Final Product
<img src=https://imgur.com/WMvAxOo.gif width=100%><br>
After working through everything this is what i finished up with ill now explain the breakdown how i got here
* #### Step 1: Making DOM Objects Drag/Drop valid
First i created a simple Document that mocks Avida-ed's layout Using Html and CSS
```HTML
<h1>Drag and Drop Example</h1>
    <div class="freezer">
      <p>Freezer</p> 
      <div class="freezerMove"> <!--Drag/Drop Valid Container-->
        <!--Using Custom data with "data-" to make keeping track of div.item information easy for more info look at https://www.w3schools.com/tags/att_global_data.asp-->
        <div class="item" style="background-color: blue;" data-OrganismType="coolOrg" data-location="-1" data-OrginismNumber="0" data-value="Cool Org"> Cool Org</div>
        <div class="item" style="background-color: pink;" data-OrganismType="warmOrg" data-location="-1" data-OrginismNumber="0" data-value="Warm Org"> Warm Org</div>
        <div class="item" style="background-color: orange;"  data-OrganismType="hotOrg" data-location="-1" data-OrginismNumber="0" data-value="Hot Org"> Hot Org</div>
      </div>
    </div>
    <div class="canvas">
    </div>
    <div class="deadZone">
      <b>deadZone</b>
    </div>
    <div class="trash">
      <p> Trash</p>
      <div class="trashMove">  <!--Drag/Drop Valid Container-->
      </div>
    </div>
  <div class="area">
      <p> Area</p>
    <div class="areaMove">   <!--Drag/Drop Valid Container-->
    </div>
  </div>
    <script src="DnD.js"></script>

```
Then i build the important Grid layouts for both the display as a whole an the cnavas which will be populated through javascript
```CSS
.canvas {
  grid-area: canvas ;
  background-color: blue;
  display: grid;  //sets up grid layout in canvas
  grid-template-columns: repeat(20, 5%); // Creates 20 columns in canvas grid
  grid-template-rows: repeat(20, 5%); // Creates 20 rows in canvas grid
}

body {
  width: 98.5%;
  display: grid;  // Sets up main grid layout in entire body
  // Creates 4 columns with set values relitive to screen size
  grid-template-columns: 10%  10% 10% 35% 15% 20%;  
  // Creates 6 rows with set values
  grid-template-rows: 100px 150px 150px 150px ;
  column-gap: 1.5%; // Gives spaces between columns
  // Puts each defined area in its place on the screen
  grid-template-areas: 
    ". . . . . ." // Creates empty first row
    ". freezer deadZone canvas . ." 
    ". . deadZone canvas area ."
    ". trash deadZone canvas . ."    ;
    border: solid 1px;
}
```

After I have the layout set up I populate the canvas with divs, using the grid layout I established earlier I fill it with 400 small '.space' divs 
```JavaScript
function createCanvas(){
  var numOfCanvasSpots = 0; // keeps track of each .space div and gives them a unique id
  for(x=0;x<400;x+=20){ // creates enough boxes for the grid 
    for(i=0;i<400;i+=20){
      $(".canvas").append("<div class=\"space\" id=\""+(numOfCanvasSpots)+"\">  </div>");  //creates new ".space" div inside canvas
      arr.push($(".space")[numOfCanvasSpots]); // pushes each new div to array that contains all valid drag/drop divs (will be explained soon)
      numOfCanvasSpots++; 
    }
  }
}
```

These divs will make up the grid that I will be allowed to drag objects into<br>
In order to do that I use the Dragula calls to create Drag/Drop vailid objects<br>
I also make objects in Freezer to where they create copies of themselves to be dragged

```JavaScript
// Populates an array that holds all the containers that will allow drag and drop
var arr = [$(".freezerMove")[0],
           $(".trashMove")[0],
           $(".areaMove")[0]]; // Along with every div in canvas that was pushed in

var dra = dragula(arr, {  // By passing in arr i make all divs in array Drag/Drop Valid
 //..
  copy: function (el, source) {
    // Makes sure the only item that will be copied instead of moved is in the FreezerMove div
    return el.parentElement.className == 'freezerMove';
  },
 //..
  revertOnSpill: true,              // spilling will put the element back where it was dragged from, if this is true
  removeOnSpill: false,              // spilling will `.remove` the element, if this is true
});

```
* #### Step 2: Control screen so that drag and drop can work correctly 
Now that the you are able to drag and drop items, depending on the size of the screen or how you want to look at the layout it may be helpful to be able to scroll and zoom. Scrolling and zooming however interfers when you are trying to drag things so this function makes it so that you cant scroll or zoom on certain objects while only using one finger. This allows everything else to stay stationary as you drag things.
```JavaScript
function controlMovment(){
  // makes sure that 1 finger touch wont move the screen in the canvas
    $(".canvas")[0].addEventListener('touchmove', function(e) {
          // screen wont move with one touch
            if (e.touches.length==1){
              e.preventDefault();
            }
    }, false);

    for (var i = 0; i < $(".item").length; i++) {
      $(".item")[i].addEventListener('touchmove', function(e) {
            // screen wont move with one touch
              if (e.touches.length==1){
                e.preventDefault();
              }
      }, false);
    }
}
```
* #### Step 3: Creating functions to achieve goals
Now that things can are drag/dropable I make sure everything works how I want it to<br>
Using the 'drop' event listener I make changes to the custom data values I have set for the '.item' object that is being moved

```JavaScript

dra.on('drop', function(el){  // A Dragula event that happens anytime an item is dropped into a valid droppable object (other than itself)
  controlMovment(); 
  // Variables that will be changed depending on where el is dropped
  var location = el.getAttribute("data-location"); // getAttribute returns the value of the given custom attribute
  var organismNumber = el.getAttribute("data-OrganismNumber");
  var value = el.getAttribute("data-value");
  
```
These lines help tell where the .item object is being dropped into and change specific data values based on which drop valid container it is dropped in
```JavaScript
  if (el.parentElement.className == 'trashMove') {  
      el.remove();  // Deletes .item object that is dropped in trash
    }else{
      if (el.parentElement.className=='space') {
        newLocation(el.parentElement.id);  // updates custom data "data-location" on element using function
        // .setAttribute sets data of given custom data in element
        el.setAttribute("data-OrganismNumber",newOrganismNumber()); // newOrganismNumber() calculates a number to set as the newOrganismNumber in data
        el.innerText = null;  // Makes text dissapear if in canvas
      }

      if (el.parentElement.className=='areaMove') {
        el.setAttribute("data-location", -1); // updates loctation to -1 if not in canvas
        el.innerText = el.getAttribute("data-value");  // Sets text to the "data-value" so text shows up when outside of canvas
      }

      if (el.parentElement.className=='freezerMove') {
        el.setAttribute("data-location", -1);
        // Using newValue function it updates the name of the orginism differentiating it from its parent organism it was originally copied from
        el.setAttribute("data-value", newValue()); 
        el.innerText = el.getAttribute("data-value");

      }


    }
```

These were all custom functions I made to help update the varibales I set at the top of the drop function<br>
They help organize what happens when things get dropped into drop valid containers
```JavaScript
  // takes in the location that .item object was placed in and updates the custom location data
  function newLocation(NEW_LOCATION){
    el.setAttribute("data-location",NEW_LOCATION);
    location = el.getAttribute("data-location");
  }
  // helps keep track of individual organism in each group Ex: shows fisrt intance of 'cool org' placed on canvas 
  function newOrganismNumber(){
    var number=0;

    for(i=0;i<$(".item").length;i++){
      if ($(".item")[i].getAttribute("data-value")==el.getAttribute("data-value")){
        number++;
        //console.log($(".item")[i]);
      }
    }
    return number-2; //subtract mirror and original org in freezer
  }

 
  function newValue(){
    var numOfItemInFreezer=0;
    for(i=0;i<$(".freezerMove .item").length;i++){
      if ($(".freezerMove .item")[i].getAttribute("data-OrganismType")==el.getAttribute("data-OrganismType")) {
        numOfItemInFreezer++;
      }
    }
    return el.getAttribute("data-value").substring(0,8)+" "+numOfItemInFreezer
  }
})


```
This is also inside of the drop function and keeps track of all the objects in the canvas

```JavaScript
    objectsInCanvas=[] // empties objectsInCanvas arr so there are no copies
    for (var i = 0; i < $(".space .item").length; i++) {
      objectsInCanvas.push($(".space .item")[i]);    // populates all array with all objects currently on canvas
    }
    console.log(objectsInCanvas)    
    returnObjectsInCanvas(); // shows information about all objects in canvas in console
```

Moving forward
--
The initial goal for this project was to make Avida-ed drag/drop features work on any device. I did not exactly meet that goal, while it looks nice and everything functions properly in the example on apple devices such as Iphones and Ipads the Scroll bar wont show up and the shadow that appears when dragging has an offset. Im sure theyre are more bugs when using different device/browser combinations but i have been able to test it on Chrome( MacOs & Windows) & FireFox( MacOs & Windows) and Safari( MacOS) and it seems to work fine there. it also works on android tablets in Chrome.

Acknowledgements
--
I would like to thank Diane and Wesley Blackwood for there help in compelting this project, Diane was an exelent mentor and helped guide the project and Wesley helped set it up on a server where it could be tested. It was a joy to work with them and all the people at the Waves Workshop.

