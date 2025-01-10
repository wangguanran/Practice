<script lang="ts" setup>
import { ref } from 'vue'

let title1 = ref()
let title2 = ref()
let title3 = ref()

function showLog() {
    // 通过id获取元素
    const t1 = document.getElementById('title1')
    console.log(t1)
    console.log((t1 as HTMLElement).innerText)
    console.log((<HTMLElement>t1).innerText)
    console.log(t1?.innerText)

    // 通过ref获取元素
    console.log(title1.value)
    console.log(title2.value)
    console.log(title3.value)
}
</script>

<template>
    <div>
        <h1 id="title1" ref="title1">尚硅谷</h1>
        <h2 ref="title2">前端</h2>
        <h3 ref="title3">Vue</h3>
        <input type="text" ref="input"><br>
        <button @click="showLog">点我打印内容</button>
        <br>
    </div>
</template>

<style scoped></style>
