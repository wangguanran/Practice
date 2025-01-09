<template>
    <div>
        <h2>汽车信息：一台 {{ car.brand }}，价值{{ car.price }}万</h2>
        <h2>游戏列表：</h2>
        <ul>
            <li v-for="g in games" :key="g.id">{{ g.name }}</li>
        </ul>
        <button @click="changeCarPrice">修改汽车价格</button>
        <button @click="changeFirstGame">修改第一游戏</button>
    </div>
</template>

<script lang="ts" setup name="Person">
import { reactive, toRef, toRefs } from 'vue'

// 数据
let car = reactive({ brand: '奔驰', price: 100 })
let games = reactive([
    { id: '001', name: '英雄联盟' },
    { id: "002", name: "王者荣耀" },
    { id: '003', name: '原神' }
])

let person = reactive({ name: 'zhangsan', age: 18, gender: 'man' })

let { name, gender } = toRefs(person)
let age = toRef(person, 'age')

// 方法
function changeCarPrice() {
    car.price += 10
}
function changeFirstGame() {
    games[0].name = '流星蝴蝶剑'
}


</script>

<style scoped></style>
