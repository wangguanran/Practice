<script setup>
import { reactive, ref, watch, watchEffect } from 'vue'

// 情况一：监视【ref】定义的【基本类型】数据
let sum = ref(0)

function changeSum() {
    sum.value += 1
}

const stopWatch = watch(sum, (newValue, oldValue) => {
    console.log('sum变化了', newValue, oldValue)
    if (newValue >= 10)
        stopWatch()
})

// 情况二：监视【ref】定义的【对象类型】数据
// 监视的是对象的地址值，若想监视对象内部属性的变化，需要手动开启深度监视
// deep为false时 只有changeperson的修改会被监视到 true时所有内部元素修改都会被监视到
// watch参数
//    1.被监视的数据
//    2.监视的回调
//    3.配置对象
let person = ref({
    name: 'zhangsan',
    age: 18
})

function changeName() {
    person.value.name += '~'
}
function changeAge() {
    person.value.age += 1
}
function changeperson() {
    person.value = { name: 'lisi', age: 18 }
}

watch(person, (newValue, oldValue) => {
    console.log('person变化了', oldValue, newValue)
}, { deep: true })

// 情况三：监视【reactive】定义的【对象类型】数据，且默认时开启深度监视的无法关闭
let person2 = reactive({
    name: 'lisi',
    age: 18
})

function changeName2() {
    person2.name += '~'
}
function changeAge2() {
    person2.age += 1
}
function changeperson2() {
    Object.assign(person2, { name: 'wangwu', age: 80 })
}

watch(person2, (newValue, oldValue) => {
    console.log('person2变化了', newValue, oldValue)
})

// 情况四：监视【ref】或【reactive】定义的【对象类型】数据中的某个属性
let person3 = reactive({
    name: 'haoche',
    age: 18,
    car: {
        c1: 'benchi',
        c2: 'baoma'
    }
})

function changeName3() {
    person3.name += '~'
}
function changeAge3() {
    person3.age += 1
}
function changeC1() {
    person3.car.c1 = 'aodi'
}
function changeC2() {
    person3.car.c2 = 'dazhong'
}
function changeCar() {
    person3.car = { c1: 'yadi', c2: 'aima' }
}
watch(() => person3.name, (newValue, oldValue) => {
    console.log('person3.name变化了', newValue, oldValue)
})
watch(() => person3.car, (newValue, oldValue) => {
    console.log("person3.car变化了", newValue, oldValue)
})

// 情况五：监视多个数据
watch([() => person3.name, person3.car], (newValue, oldValue) => {
    console.log('person.name或person.car变化了', newValue, oldValue)
})


// watchEffect
watchEffect(() => {
    console.log('watchEffect进来了')
    if (person3.age > 25) {
        console.log('1111111111')
    }
})
</script>

<template>
    <div>
        <h1>当前求和为：{{ sum }}</h1>
        <button @click="changeSum">点我sum+1</button>
        <br>
        <h2>姓名：{{ person.name }}</h2>
        <h2>年龄：{{ person.age }}</h2>
        <button @click="changeName">修改姓名</button>
        <button @click="changeAge">修改年龄</button>
        <button @click="changeperson">修改全部</button>
        <br>
        <h2>姓名：{{ person2.name }}</h2>
        <h2>年龄：{{ person2.age }}</h2>
        <button @click="changeName2">修改姓名</button>
        <button @click="changeAge2">修改年龄</button>
        <button @click="changeperson2">修改全部</button>
        <br>
        <h2>姓名：{{ person3.name }}</h2>
        <h2>年龄：{{ person3.age }}</h2>
        <h2>汽车：{{ person3.car.c1 }}、{{ person3.car.c2 }}</h2>
        <button @click="changeName3">修改名字</button>
        <button @click="changeAge3">修改年龄</button>
        <button @click="changeC1">修改第一台车</button>
        <button @click="changeC2">修改第二台车</button>
        <button @click="changeCar">修改整个车</button>
    </div>
</template>

<style scoped></style>
