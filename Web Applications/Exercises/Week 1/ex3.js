function Answer(response, respondent_name, score, date) {
    this.response = response
    this.respondent_name = respondent_name
    this.score = score
    this.date = date
}

function Question(question, questioner_name, date) {
    this.question = question
    this.questioner_name = questioner_name
    this.date = date
    this.answers = []
    this.add = function (answer) {
        this.answers.push(answer)
    }
    this.findAll = function (name) {
        return this.answers.filter(ans => ans['respondent_name'] === name)
    }
    this.afterDate = function (date) {
        return this.answers.filter(ans => ans['date'] > date)
    }
    this.listByDate = function () {
        return this.answers.sort((a, b) => a.date.getTime() - b.date.getTime())
    }
    this.listByScore = function () {
        return this.answers.sort((a, b) => b.score - a.score)
    }
}

const ans1 = new Answer("good", "Bob", 10, new Date("2024-10-10"))
const ans2 = new Answer("good", "Carl", 4, new Date("2024-10-10"))
const ans3 = new Answer("good", "Eve", 6, new Date("2024-10-9"))
const ans4 = new Answer("good", "John", 10, new Date("2024-10-8"))

const qst = new Question("?", "Anne", new Date("2024-10-7"))

qst.add(ans1)
qst.add(ans2)
qst.add(ans3)
qst.add(ans4)

console.log("All answers by 'Bob': ")
console.log(qst.findAll("Bob"))

console.log("\nAnswers after October 9: ")
console.log(qst.afterDate(new Date("2024-10-9")))

console.log("\nAnswers by date (asc): ")
console.log(qst.listByDate())

console.log("\nAnswers by score (desc): ")
console.log(qst.listByScore())


