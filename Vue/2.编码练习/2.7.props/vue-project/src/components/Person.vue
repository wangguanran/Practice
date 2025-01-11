<template>
    <div class="person">
        <ul>
            <li v-for="item in list" :key="item.id">
                {{ item.name }}--{{ item.age }}
            </li>
        </ul>
    </div>
</template>

<script lang="ts" setup name="Person">
import { defineProps } from 'vue'
import { Persons, type PersonInter } from '@/types'

// const props = defineProps(['list'])

// defineProps<{ list: Persons }>()

let props = withDefaults(defineProps<{ list: Persons }>(), {
    list: () => [{ id: "1", name: 'zhangsan', age: 18 }]
})

console.log(props)
</script>