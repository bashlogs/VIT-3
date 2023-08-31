function getResult() {
    const rollNumber = document.getElementById("roll-number").value;

    fetch(`/get-result?rollNumber=${rollNumber}`)
        .then(response => response.json())
        .then(data => {
            const resultContainer = document.getElementById("result-container");
            resultContainer.innerHTML = `
                <p>Subject 1 Total: ${data.subject1Total}</p>
                <!-- Repeat for other subjects -->
            `;
        })
        .catch(error => {
            console.error("Error fetching result:", error);
        });
}
