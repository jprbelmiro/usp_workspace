var displayedImage = document.querySelector('.displayed-img');
var thumbBar = document.querySelector('.thumb-bar');

btn = document.querySelector('button');
var overlay = document.querySelector('.overlay');

/* Display Image Function*/
function displayImage(e){
	new_src = e.target.getAttribute("src")
	displayedImage.src = new_src;
}

/* Looping through images */
for(let img_count = 1; img_count <= 5 ; img_count++){
  var newImage = document.createElement('img');
  newImage.setAttribute('src', 'images/pic'+img_count+'.jpg');

  newImage.onclick = displayImage;

  thumbBar.appendChild(newImage);
}

/* Darken/Lighten Function*/
function switchLight(){
	cur_class = btn.getAttribute("class");
	if(cur_class == "dark"){
		btn.setAttribute('class', "light");
		btn.textContent = 'Lighten';
		overlay.style.backgroundColor = "rgba(0,0,0,0.5)";
	}
	else{
		btn.setAttribute('class', "dark");
		btn.textContent = 'Darken';
		overlay.style.backgroundColor = "rgba(0,0,0,0)";
	}
}

/* Wiring up the Darken/Lighten button */
btn.onclick = switchLight;