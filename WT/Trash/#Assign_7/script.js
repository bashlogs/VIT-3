document.getElementById("result-form").addEventListener("submit", function (event) {
    event.preventDefault();
    
    const rollNumber = document.getElementById("roll-number").value;
    
    fetch("result.php", {
        method: "POST",
        body: new URLSearchParams({
            rollNumber: rollNumber
        })
    })
    .then(response => response.json())
    .then(data => {
        const resultContainer = document.getElementById("result-container");
        resultContainer.style.display = "block";
        resultContainer.innerHTML = `
            <p>Subject 1: ${data.subject1}</p>
            <!-- Repeat the above line for the other subjects -->
        `;
    })
    .catch(error => {
        console.error("Error fetching result:", error);
    });
});
