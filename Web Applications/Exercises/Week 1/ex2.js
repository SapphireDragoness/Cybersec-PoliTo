// Define the names as a comma-separated string containing the names
const names_string = "Luigi De Russis, Luca Mannella, Fulvio Corno, Juan Pablo Saenz Moreno, Enrico Masala, Antonio Servetti"

// Parse the string and create an array containing one name per array position
let names_array = names_string.split(", ")

// Create a second array by computing the acronyms of the people as the initial letters of the name
let acronyms = names_array.map((e) => e.match(/[A-Z]/g).join("")).sort()

console.log("Names: " + names_array)
console.log("Acronyms: " + acronyms)